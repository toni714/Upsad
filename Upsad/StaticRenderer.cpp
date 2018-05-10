#include "StaticRenderer.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

StaticRenderer::StaticRenderer()
{
	inc = 0;
}

void StaticRenderer::addInstance(const Instance * instance)
{
	std::map<const RawModel*, std::vector<const Instance*>>::iterator pos = models.find(instance->getModel());
	if (pos!=models.end()) {
		pos->second.push_back(instance);
	}
	else {
		models.insert(std::pair<const RawModel*, std::vector<const Instance*>>(instance->getModel(), std::vector<const Instance*>{instance}));
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

void StaticRenderer::prepareInstance(const Instance * instance)
{
	glm::mat4 mvp=glm::mat4(1.0);
	mvp=glm::translate(mvp, instance->getPos());
	glm::vec3 rot = instance->getRot();
	mvp=glm::scale(mvp, glm::vec3(instance->getScale()*0.5));
	mvp = glm::rotate(mvp, rot.x, glm::vec3(1, 0, 0));
	mvp = glm::rotate(mvp, rot.y, glm::vec3(0, 1, 0));
	mvp = glm::rotate(mvp, rot.z, glm::vec3(0, 0, 1));
	mvp=glm::rotate(mvp, inc, glm::vec3(5, 8, 13));
	inc += 0.01;
	shader.loadMVPMatrix(mvp);
}

void StaticRenderer::render()
{
	//replace int with instance
	prepare();
	auto modelIT= models.begin();
	for (; modelIT != models.end(); modelIT++) {
		const RawModel* model = modelIT->first;
		prepareModel(model);
		std::vector<const Instance*> instances=modelIT->second;
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
