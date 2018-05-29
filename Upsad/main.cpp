#include <chrono>
#include <thread>
#include <glm\vec3.hpp>

#include "WindowManager.h"
#include "StaticRenderer.h"
#include "TexturedModel.h"
#include "Instance.h"
#include "ModelHelper.h"

WindowManager* windowManager;
StaticRenderer* staticRenderer;

TexturedModel* texModel;
Instance* instance;

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
	if (windowManager != nullptr) {
		delete windowManager;
	}
}

void setupUtility() {
	windowManager = new WindowManager(UPSAD::WIDTH, UPSAD::HEIGHT, UPSAD::TITLE);
	staticRenderer = new StaticRenderer();
}

void loadModel() {
	texModel = TexturedModel::loadFromFiles("tree.obj", "tree.bmp");
	instance = Instance::createInstance(texModel, glm::vec3(0, -2, -10), glm::vec3(0, 0, 0), 1);
}

void handleEvents() {
	windowManager->pollEvents();
}

void update() {
	//pass (for now)
}

void draw() {
	staticRenderer->addInstance(instance);
	staticRenderer->render();
	staticRenderer->clearQueue();
	windowManager->swapBuffers();
}

void sleep() {
	std::this_thread::sleep_for(std::chrono::milliseconds(17));
}

bool appIsRunning() {
	return !windowManager->shouldClose();
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