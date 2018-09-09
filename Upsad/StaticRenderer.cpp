#include "StaticRenderer.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

StaticRenderer::StaticRenderer() noexcept
{
}

void StaticRenderer::loadProjectionMatrix(const float& fov, const float& screenRatio, const float& nearPlane, const float& farPlane)
{
	shader.start();
	shader.loadProjectionMatrix(glm::perspective(fov, screenRatio, nearPlane, farPlane));
	shader.stop();
}

void StaticRenderer::loadLight(const Light & light)
{
	shader.start();
	shader.loadLight(light);
	shader.stop();
}

void StaticRenderer::loadCamera(const Camera& camera)
{
	shader.loadCamera(camera);
}

void StaticRenderer::addInstance(const Instance* instance)
{
	std::unordered_map<std::shared_ptr<RawModel>, std::vector<const Instance*>>::iterator pos = queue.find(instance->texturedModel->model);
	if (pos != queue.end()) {
		pos->second.push_back(instance);
	}
	else {
		queue.insert(std::pair<std::shared_ptr<RawModel>, std::vector<const Instance*>>(instance->texturedModel->model, std::vector<const Instance*>{ instance }));
	}
}

void StaticRenderer::clearQueue()
{
	queue.clear();
}

void StaticRenderer::prepare() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	shader.start();
}

void StaticRenderer::prepareModel(std::shared_ptr<RawModel> model)
{
	glBindVertexArray(model->vaoID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}

void StaticRenderer::prepareInstance(const Instance* instance)
{
	shader.loadModelMatrix(instance->getModelMatrix());
	prepareTexture(instance->texturedModel->texture);
}

void StaticRenderer::prepareTexture(std::shared_ptr<ImageTexture> texture)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->id);
}

void StaticRenderer::render()
{
	prepare();
	for (const auto& queueIT : queue) {
		std::shared_ptr<RawModel> model = queueIT.first;
		prepareModel(model);
		for (const auto& instanceIT : queueIT.second) {
			prepareInstance(instanceIT);
			glDrawElements(GL_TRIANGLES, model->vertexCount, GL_UNSIGNED_INT, 0);
		}
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
	glBindVertexArray(0);
	shader.stop();
}