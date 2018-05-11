#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

class WindowManager
{
private:
	GLFWwindow * window;
	void setWindowHints(const int& versionMajor, const int& versionMinor, const int& openGLProfile, const int& resizeable);
public:
	WindowManager(const int& width, const int& height, const char* title);
	~WindowManager();
	bool shouldClose() const;
	void pollEvents() const;
	void swapBuffers() const;
};
