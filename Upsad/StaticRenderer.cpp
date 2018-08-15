#include "StaticRenderer.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

StaticRenderer::StaticRenderer() noexcept
{
	inc = 0;//TODO remove this
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

void StaticRenderer::addInstance(const Instance * instance)
{
	std::unordered_map<const RawModel*, std::vector<const Instance*>>::iterator pos = queue.find(instance->texturedModel->model);
	if (pos != queue.end()) {
		pos->second.push_back(instance);
	}
	else {
		queue.insert(std::pair<const RawModel*, std::vector<const Instance*>>(instance->texturedModel->model, std::vector<const Instance*>{instance}));
		
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

void StaticRenderer::prepareModel(const RawModel * model)
{
	glBindVertexArray(model->vaoID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}

void StaticRenderer::prepareInstance(const Instance * instance)
{
	glm::mat4 modelMatrix = glm::mat4(1.0);
	modelMatrix = glm::translate(modelMatrix, instance->position);

	modelMatrix = glm::scale(modelMatrix, glm::vec3(instance->scale*0.5f));

	glm::vec3 rot = instance->rotation;
	modelMatrix = glm::rotate(modelMatrix, rot.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, rot.y + inc, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, rot.z, glm::vec3(0, 0, 1));
	//inc += 0.01f;
	shader.loadModelMatrix(modelMatrix);
	prepareTexture(instance->texturedModel->texture);
}

void StaticRenderer::prepareTexture(const ImageTexture * texture)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->id);
}

void StaticRenderer::render()
{
	prepare();
	for (const auto& queueIT : queue) {
		const RawModel* model = queueIT.first;
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