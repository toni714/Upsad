#include "StaticRenderer.h"
#include "WindowManager.h"
#include "ModelHelper.h"
#include "TextureHelper.h"

#include <glm/gtc/constants.hpp>
#include "Terrain.h"
#include <thread>
#include <chrono>
#include <iostream>

StaticRenderer* staticRenderer;

TexturedModel* texModel;
TexturedModel* texModel2;
Instance* instance;
std::vector<Instance*> instances;
Camera* camera;
float inc = 0;

namespace UPSAD {
	const int WIDTH = 800;
	const int HEIGHT = 600;
	const char* TITLE = "Hello OpenGL";
}

void cleanup() {
	if (instance != nullptr) {
		delete instance;
	}
	if (texModel != nullptr) {
		delete texModel;
	}
	TextureHelper::cleanup();
	ModelHelper::cleanup();
	WindowManager::cleanup();
}

void setupUtility() {
	WindowManager::createWindow(UPSAD::WIDTH, UPSAD::HEIGHT, UPSAD::TITLE);

	staticRenderer = new StaticRenderer();
	staticRenderer->loadProjectionMatrix(glm::pi<float>() / 4.0f, UPSAD::WIDTH / (float)UPSAD::HEIGHT, 0.1f, 100.0f);
	staticRenderer->loadLight(Light(glm::vec3(0, 3, 0), glm::vec3(1, 1, 1)));

	camera = new Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	staticRenderer->loadCamera(*camera);
}

void loadModel() {
	//Terrain* t = new Terrain(glm::vec3(0,0,0),glm::vec3(0,0,0), 1,1,1);
	std::shared_ptr<RawModel> model=Terrain::generateTerrain(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 100, 2, 20);
	//__debugbreak();
	texModel = new TexturedModel(model, TextureHelper::getTextureFromFile("tree.bmp"));
	texModel2 = new TexturedModel(ModelHelper::getModelFromFile("tree.obj"), TextureHelper::getTextureFromFile("tree.bmp"));
	instance = new Instance(texModel, glm::vec3(0, -2, -10), glm::vec3(0, 0, 0), 1);
	for (int i = 0; i < 100; i++) {
		float x = ((rand() / (float)RAND_MAX) - 0.5f) * 100;
		float z = ((rand() / (float)RAND_MAX) - 0.5f) * 100;
		instances.push_back(new Instance(texModel2, glm::vec3(x, -2, z), glm::vec3(0, 0, 0), 1));
	}
}

void handleEvents() {
	WindowManager::pollEvents();
}

/*void moveCamera() {
	camera->getNextPosition();
	staticRenderer->loadCamera(*camera);
}*/

void update() {
	glm::vec3 nextPosition=camera->getNextPosition();
	bool collision = false;
	for (const auto& _instance : instances) {
		if (_instance->collidesWith(nextPosition)) {
			collision = true;
		}
	}
	if (!collision) {
		camera->position = nextPosition;
	}
	staticRenderer->loadCamera(*camera);
}

void draw() {
	staticRenderer->addInstance(instance);
	for (const auto& _instance : instances) {
		staticRenderer->addInstance(_instance);
	}
	staticRenderer->render();
	staticRenderer->clearQueue();
	WindowManager::swapBuffers();
}

void sleep() {
	std::this_thread::sleep_for(std::chrono::milliseconds(17));
}

bool appIsRunning() {
	return !WindowManager::shouldClose();
}

void gameloop() {
	while (appIsRunning()) {
		handleEvents();
		update();
		draw();
		sleep();
	}
}

int main(int argc, char** argv) {
	//__debugbreak();
	try {
		setupUtility();
		loadModel();
		gameloop();
	}
	catch (std::runtime_error e) {
		std::cerr << e.what() << std::endl;
		cleanup();
		system("pause");
		return EXIT_FAILURE;
	}

	cleanup();
	//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	//__debugbreak();
	return EXIT_SUCCESS;
}