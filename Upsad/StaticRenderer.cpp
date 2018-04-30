#include "StaticRenderer.h"

void StaticRenderer::addInstance(const RawModel * model)//Replace with Instance
{
	//Replace this(int) with instance
	std::map<const RawModel*, std::vector<int>>::iterator pos = models.find(model);//instance->getModel()
	if (pos!=models.end()) {
		//pos->second.push_back(instance);
	}
	else {
		models.insert(std::pair<const RawModel*, std::vector<int>>(model, std::vector<int>{0}));
	}
}

void StaticRenderer::clearQueue()
{
	models.clear();//Does this delete RawModels/Instances?
}

void StaticRenderer::prepare() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void StaticRenderer::prepareModel(const RawModel * model)
{
	glBindVertexArray(model->getVaoID());
}

void StaticRenderer::render()
{
	//replace int with instance
	prepare();
	std::map<const RawModel*, std::vector<int>>::iterator modelIT;
	for (modelIT = models.begin(); modelIT != models.end(); modelIT++) {
		const RawModel* model = modelIT->first;
		prepareModel(model);
		std::vector<int> instances=modelIT->second;
		std::vector<int>::iterator instanceIT;

		for (instanceIT = instances.begin(); instanceIT != instances.end(); instanceIT++) {
			//prepareInstance(*instanceIT);
			glDrawElements(GL_TRIANGLES, model->getVertexCount(), GL_UNSIGNED_SHORT, 0);
		}
	}
	glBindVertexArray(0);

}
