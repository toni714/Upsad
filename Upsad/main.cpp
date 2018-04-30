
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <vector>

#include "ModelHelper.h"
#include "RawModel.h"

#include <chrono>//DEBUG
#include <thread>//DEBUG

std::vector<GLfloat> vertices =
{
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f
};

namespace UPSAD {
	const int WIDTH = 800;
	const int HEIGHT = 600;
	GLFWwindow* window;
}

void initWindow() {
	using namespace UPSAD;
	//Init GLFW
	if (!glfwInit()) {
		throw std::runtime_error("Error! Failed to initialize the Windowing Library!");
	}
	//Setup Window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //OSX
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//Create Window
	window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Tutorial", nullptr, nullptr);

	if (window == NULL) {
		glfwTerminate();
		throw std::runtime_error("Error! Failed to create Window");
	}
	glfwMakeContextCurrent(window);

}

void initGL() {
	using namespace UPSAD;
	//Init GLAD/OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Error! Failed to initialize OpenGL");
	}

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	glViewport(0, 0, screenWidth, screenHeight);

}

int main() {
	using namespace UPSAD;
	try{
		initWindow();
		initGL();
	}
	catch (std::runtime_error e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	
	ModelHelper* modelHelper = new ModelHelper();
	
	//Init Model
	RawModel* model = modelHelper->loadToVAO(vertices);

	//Main Loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(model->getVaoID());
		glDrawArrays(GL_TRIANGLES, 0, (model->getVertexCount() / 3));
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	delete model;
	delete modelHelper;

	//Quit
	glfwTerminate();
	return EXIT_SUCCESS;
}