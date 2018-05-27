#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <vector>

#include "Utility.h"
#include "RawModel.h"
#include "StaticRenderer.h"
#include "Instance.h"
#include "WindowManager.h"
#include "ImageTexture.h"
#include "TexturedModel.h"

#include <chrono>//DEBUG
#include <thread>//DEBUG

#include <glm\vec3.hpp>

WindowManager* windowManager;
StaticRenderer* staticRenderer;

RawModel* model;
Instance* instance;

namespace UPSAD {
	const int WIDTH = 800;
	const int HEIGHT = 600;
	const char* TITLE = "Hello OpenGL";
}

void cleanup() {
	if (model != nullptr) {
		delete model;
	}
	if (Utility::modelHelper != nullptr) {
		delete Utility::modelHelper;
	}
	if (windowManager != nullptr) {
		delete windowManager;
	}
}

void setupUtility() {
	windowManager = new WindowManager(UPSAD::WIDTH, UPSAD::HEIGHT, UPSAD::TITLE);
	Utility::modelHelper = new ModelHelper();
	staticRenderer = new StaticRenderer();
}

void loadModel() {
	model = FileUtil::loadOBJ("tree.obj");
	GLuint textureID = FileUtil::load_BMP("tree.bmp");
	ImageTexture* texture = new ImageTexture(textureID);
	TexturedModel* texModel = new TexturedModel(model, texture);
	instance = new Instance(texModel, glm::vec3(0, -2, -10), glm::vec3(0, 0, 0), 1);
}

void handleEvents() {
	windowManager->pollEvents();
}

void update() {
	staticRenderer->addInstance(instance);//Maybe move this to draw
}

void draw() {
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

int main() {
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