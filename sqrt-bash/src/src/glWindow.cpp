#include "glWindow.h"

Window::Window()
{
    width = 800;
    height = 600;
}
Window::Window(int windowWidth, int windowHeight)
{
	width = (GLint)windowWidth;
	height = (GLint)windowHeight;
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

int Window::Init()
{
	if (!glfwInit()) {
		printf("GLFW initialisation failed!");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!mainWindow) {
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(mainWindow);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("GLEW initialisation failed!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	
	glViewport(0, 0, bufferWidth, bufferHeight);
	


}

GLint Window::getBufferWidth()
{
    return bufferWidth;
}

GLint Window::getBufferHeight()
{
    return bufferHeight;
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(mainWindow);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(mainWindow);
}
