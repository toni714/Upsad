#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class WindowManager
{
private:
	static GLFWwindow * window;
	static void setWindowHints(const int& versionMajor, const int& versionMinor, const int& openGLProfile, const int& resizeable);
public:
	static void createWindow(const int& width, const int& height, const char* title);
	static void cleanup();
	static GLFWwindow* getWindowReference();
	static bool shouldClose();
	static void pollEvents();
	static void swapBuffers();
};
