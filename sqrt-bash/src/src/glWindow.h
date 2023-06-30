#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

class Window {
public:
	Window();
	Window(int windowWidth, int windowHeight);
	~Window();
	
	int Init();
	GLint getBufferWidth();
	GLint getBufferHeight();
	
	bool shouldClose();
	void swapBuffers();
private:
	GLFWwindow* mainWindow;
	GLint width, height;
	GLint bufferWidth, bufferHeight;
};
