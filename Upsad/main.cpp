
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

float vertices[] =
{
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f
};

namespace UPSAD {
	const int WIDTH = 800;
	const int HEIGHT = 600;
}

int main() {
	//Init GLFW
	if (!glfwInit()) {
		std::cerr << "Error! Failed to initialize the Windowing Library!" << std::endl;
		return EXIT_FAILURE;
	}
	//Setup Window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //OSX
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	
	//Create Window
	GLFWwindow* window = glfwCreateWindow(UPSAD::WIDTH, UPSAD::HEIGHT, "OpenGL Tutorial", nullptr, nullptr);

	int screenWidth, screenHeight;	
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (window == NULL) {
		std::cerr << "Error! Failed to create Window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);

	//Init GLAD/OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Error! Failed to initialize OpenGL" << std::endl;
		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	//Init Model
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	

	//Main Loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(vaoID);
		glDrawArrays(GL_TRIANGLES, 0, (sizeof(vertices) / sizeof(*vertices) / 3));
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	//Quit
	glfwTerminate();
	return EXIT_SUCCESS;
}