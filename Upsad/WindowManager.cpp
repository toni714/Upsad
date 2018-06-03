#include "WindowManager.h"

void WindowManager::setWindowHints(const int& versionMajor, const int& versionMinor, const int& openGLProfile, const int& resizeable)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);

	glfwWindowHint(GLFW_OPENGL_PROFILE, openGLProfile);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Apple
	glfwWindowHint(GLFW_RESIZABLE, resizeable);
}

void WindowManager::createWindow(const int & width, const int & height, const char * title)
{
	if (!glfwInit()) {
		throw std::runtime_error("Error! Failed to initialize the Windowing Library!");
	}
	setWindowHints(4, 0, GLFW_OPENGL_CORE_PROFILE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (window == NULL) {
		throw std::runtime_error("Error! Failed to create Window");
	}
	glfwMakeContextCurrent(window);

	//

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Error! Failed to initialize OpenGL");
	}

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	glViewport(0, 0, screenWidth, screenHeight);
}

void WindowManager::cleanup()
{
	glfwDestroyWindow(window);
	window = nullptr;
	glfwTerminate();
}

GLFWwindow * WindowManager::getWindowReference()
{
	return window;
}

bool WindowManager::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void WindowManager::pollEvents()
{
	glfwPollEvents();
}

void WindowManager::swapBuffers()
{
	glfwSwapBuffers(window);
}

GLFWwindow* WindowManager::window = nullptr;