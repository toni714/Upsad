#include "StaticRenderer.h"

void StaticRenderer::addInstance(const Instance * instance)//Replace with Instance
{
	//Replace this(int) with instance
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
	models.clear();//Does this delete RawModels/Instances?
}

void StaticRenderer::prepare() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader.start();
}

void StaticRenderer::prepareModel(const RawModel * model)
{
	glBindVertexArray(model->getVaoID());
}

void StaticRenderer::render()
{
	//replace int with instance
	prepare();
	std::map<const RawModel*, std::vector<const Instance*>>::iterator modelIT;
	for (modelIT = models.begin(); modelIT != models.end(); modelIT++) {
		const RawModel* model = modelIT->first;
		prepareModel(model);
		std::vector<const Instance*> instances=modelIT->second;
		std::vector<const Instance*>::iterator instanceIT;

		for (instanceIT = instances.begin(); instanceIT != instances.end(); instanceIT++) {
			//prepareInstance(*instanceIT);
			glDrawElements(GL_TRIANGLES, model->getVertexCount(), GL_UNSIGNED_SHORT, 0);
		}
	}
	glBindVertexArray(0);
	shader.stop();
}
