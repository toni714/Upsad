#include <chrono>
#include <thread>
#include <glm\vec3.hpp>

#include "WindowManager.h"
#include "StaticRenderer.h"
#include "TexturedModel.h"
#include "Instance.h"
#include "ModelHelper.h"
#include "Camera.h"
#include "Keys.h"

StaticRenderer* staticRenderer;

TexturedModel* texModel;
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
	ModelHelper::cleanup();
	WindowManager::cleanup();
}

void setupUtility() {
	WindowManager::createWindow(UPSAD::WIDTH, UPSAD::HEIGHT, UPSAD::TITLE);

	staticRenderer = new StaticRenderer();
	staticRenderer->loadProjectionMatrix(glm::pi<float>()/4.0f, UPSAD::WIDTH/(float)UPSAD::HEIGHT, 0.1f, 100.0f);
	staticRenderer->loadLight(Light(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
	
	camera = new Camera(glm::vec3(0,0,0), glm::vec3(0,0,0));
	staticRenderer->loadCamera(*camera);
}

void loadModel() {
	texModel = new TexturedModel(ModelHelper::getModelFromFile("tree.obj"), ModelHelper::getTextureFromFile("tree.bmp"));
	instance = new Instance(texModel, glm::vec3(0, -2, -10), glm::vec3(0, 0, 0), 1);
	for (int i = 0; i < 100; i++) {
		float x = ((rand() / (float)RAND_MAX) - 0.5) * 100;
		float z = ((rand() / (float)RAND_MAX) - 0.5) * 100;
		instances.push_back(new Instance(texModel, glm::vec3(x,-2,z), glm::vec3(0,0,0), 1));
	}
}

void handleEvents() {
	WindowManager::pollEvents();
}

void moveCamera() {
	if (Keys::FORWARD.isPressed()) {
		camera->moveForward(0.1f);
	}
	if (Keys::BACKWARD.isPressed()) {
		camera->moveForward(-0.1f);
	}
	if (Keys::LEFT.isPressed()) {
		camera->moveSideways(-0.1f);
	}
	if (Keys::RIGHT.isPressed()) {
		camera->moveSideways(0.1f);
	}
	if (Keys::TURN_LEFT.isPressed()) {
		camera->rotation += glm::vec3(0, glm::radians(1.f), 0);
	}
	if (Keys::TURN_RIGHT.isPressed()) {
		camera->rotation += glm::vec3(0, glm::radians(-1.f), 0);
	}
	staticRenderer->loadCamera(*camera);
}

void update() {
	moveCamera();
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
	return EXIT_SUCCESS;
}