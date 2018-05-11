
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

std::vector<GLfloat> vertices =
{
	- 1.000000, - 1.000000, 1.000000,
	- 1.000000, 1.000000, 1.000000,
	- 1.000000, - 1.000000, - 1.000000,
	- 1.000000, 1.000000, - 1.000000,
	1.000000, - 1.000000, 1.000000,
	1.000000, 1.000000, 1.000000,
	1.000000, - 1.000000, - 1.000000,
	1.000000, 1.000000, - 1.000000
};

std::vector<GLfloat> uvs = {
	0.000000, 0.000000,
	0.000000, 1.000000,
	1.000000, 1.000000,
	1.000000, 0.000000,
	0.000000, 0.000000,
	0.000000, 1.000000,
	1.000000, 1.000000,
	1.000000, 0.000000,
	0.000000, 0.000000,
	0.000000, 1.000000,
	- 1.000000, 1.000000,
	- 1.000000, 0.000000,
	0.000000, 0.000000,
	0.000000, 1.000000,
	- 1.000000, 1.000000,
	- 1.000000, 0.000000,
	1.000000, - 1.000000,
	0.000000, - 1.000000,
	0.000000, 0.000000,
	- 1.000000, 0.000000,
	- 1.000000, - 1.000000,
	0.000000, - 1.000000,
};

std::vector<GLuint> indices=
{
	0, 1, 3,
	3, 1, 2,
	1, 5, 2,
	2, 5, 6,
	5, 4, 6,
	6, 4, 7,
	4, 0, 7,
	7, 0, 3,
	3, 2, 7,
	7, 2, 6,
	4, 5, 0,
	0, 5, 1
};

WindowManager* windowManager;

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

int main() {
	try {
		windowManager = new WindowManager(UPSAD::WIDTH, UPSAD::HEIGHT, UPSAD::TITLE);
		Utility::modelHelper = new ModelHelper();
		
		model=FileUtil::loadOBJ("cube.obj");
		//model = Utility::modelHelper->loadToVAO(vertices, uvs, indices);
		GLuint textureID = FileUtil::load_BMP("test2.bmp");
		ImageTexture* texture = new ImageTexture(textureID);
		TexturedModel* texModel = new TexturedModel(model, texture);
		instance = new Instance(texModel, glm::vec3(0,0,0), glm::vec3(0,0,0), 1);

		StaticRenderer sr;

		while (!windowManager->shouldClose()) {
			windowManager->pollEvents();
			sr.render(instance);

			windowManager->swapBuffers();
			std::this_thread::sleep_for(std::chrono::milliseconds(17));
		}
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