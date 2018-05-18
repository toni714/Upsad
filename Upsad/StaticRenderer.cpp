#include "StaticRenderer.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

StaticRenderer::StaticRenderer()
{
	inc = 0;
}

void StaticRenderer::addInstance(const Instance * instance)
{
	std::map<const RawModel*, std::vector<const Instance*>>::iterator pos = models.find(instance->getTexModel()->getModel());
	if (pos != models.end()) {
		pos->second.push_back(instance);
	}
	else {
		models.insert(std::pair<const RawModel*, std::vector<const Instance*>>(instance->getTexModel()->getModel(), std::vector<const Instance*>{instance}));
	}
}

void StaticRenderer::clearQueue()
{
	models.clear();
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
	glBindVertexArray(model->getVaoID());
	glEnableVertexAttribArray(0);
}

void StaticRenderer::prepareTexture(const ImageTexture * texture)
{
}

void StaticRenderer::prepareInstance(const Instance * instance)
{
	glm::mat4 mvp = glm::mat4(1.0);
	mvp = glm::translate(mvp, instance->getPos());
	mvp = glm::translate(mvp, glm::vec3(0, 0, -5));
	glm::vec3 rot = instance->getRot();
	mvp = glm::scale(mvp, glm::vec3(instance->getScale()*0.5f));
	mvp = glm::rotate(mvp, rot.x, glm::vec3(1, 0, 0));
	mvp = glm::rotate(mvp, rot.y, glm::vec3(0, 1, 0));
	mvp = glm::rotate(mvp, rot.z, glm::vec3(0, 0, 1));
	mvp = glm::rotate(mvp, inc, glm::vec3(0, 1, 0));
	inc += 0.01f;
	
	shader.loadModelMatrix(mvp);
	glm::mat4 pm = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f)*mvp;
	shader.loadProjectionMatrix(pm);
	prepareTexture(instance->getTexModel()->getTexture());
}

void StaticRenderer::render()
{
	//replace int with instance
	prepare();
	auto modelIT = models.begin();
	for (; modelIT != models.end(); modelIT++) {
		const RawModel* model = modelIT->first;
		prepareModel(model);
		std::vector<const Instance*> instances = modelIT->second;
		auto instanceIT = instances.begin();
		for (; instanceIT != instances.end(); instanceIT++) {
			prepareInstance(*instanceIT);
			glDrawElements(GL_TRIANGLES, model->getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		glDisableVertexAttribArray(0);
	}
	glBindVertexArray(0);
	shader.stop();
}

void StaticRenderer::render(const Instance * instance)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	shader.start();

	TexturedModel* texModel = instance->getTexModel();
	RawModel* model = texModel->getModel();
	glBindVertexArray(model->getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texModel->getTexture()->getID());

	glm::mat4 mvp = glm::mat4(1.0);
	mvp = glm::translate(mvp, instance->getPos());
	mvp = glm::translate(mvp, glm::vec3(0, 0, -5));
	glm::vec3 rot = instance->getRot();
	mvp = glm::scale(mvp, glm::vec3(instance->getScale()*0.5f));
	mvp = glm::rotate(mvp, rot.x, glm::vec3(1, 0, 0));
	mvp = glm::rotate(mvp, rot.y, glm::vec3(0, 1, 0));
	mvp = glm::rotate(mvp, rot.z, glm::vec3(0, 0, 1));
	mvp = glm::rotate(mvp, inc, glm::vec3(0, 1, 0));
	inc += 0.01f;
	shader.loadModelMatrix(mvp);
	shader.loadProjectionMatrix(glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f));
	shader.loadLight(Light(glm::vec3(-5, -1, 4), glm::vec3(1,1,1)));

	prepareTexture(texModel->getTexture());
	glDrawElements(GL_TRIANGLES, model->getVertexCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
	shader.stop();
}