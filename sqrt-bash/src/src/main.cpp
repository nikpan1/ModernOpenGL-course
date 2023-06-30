#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\mat4x4.hpp>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "glWindow.h"
#include "Camera.h"


const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14159265f / 180.f;

Window* mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
Camera* camera;

GLfloat deltaTime = 0.f;
GLfloat lastTime = 0.f;

static const char* vertexShader = "shaders/shader.vs";
static const char* fragmenShader = "shaders/shader.fs";

void CreateObject() {
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};
	
	Mesh* obj1 = new Mesh();
	obj1->Create(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

void CreateShaders() {
	Shader* shader1 = new Shader();
	shader1->CreateFromFile(vertexShader, fragmenShader);
	shaderList.push_back(shader1);
}


int main() {
	mainWindow = new Window(WIDTH, HEIGHT);
	mainWindow->Init();

	CreateObject();
	CreateShaders();
	
	camera = new Camera(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f), -90.f, 0.f, 5.f, 0.5f);

	float FOV = 45.f;
	float aspect_ratio = mainWindow->getBufferWidth() / mainWindow->getBufferHeight();
	float  zNear = 0.1f, zFar = 100.f;
	glm::mat4 projection = glm::perspective(FOV, aspect_ratio, zNear, zFar);

	GLuint uniformProjection{ 0 }, uniformModel{ 0 }, uniformView { 0 };
	glm::mat4 model = glm::mat4(1.0f);

	while (!mainWindow->shouldClose()) {

		GLfloat now = glfwGetTime(); // in seconds
		deltaTime = now - lastTime;
		lastTime = now;

		// user input
		glfwPollEvents();
		camera->keyControl(mainWindow->getsKeys(), deltaTime);
		camera->mouseControl(mainWindow->getXChange(), mainWindow->getYChange());

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->Use();
		uniformProjection = shaderList[0]->GetProjectionLocation();
		uniformModel = shaderList[0]->GetModelLocation();
		uniformView = shaderList[0]->GetViewLocation();


		// it's important to initialize an indetity matrix with constructor
		model = glm::mat4(1.0f);
		// the order is important	p v m
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
		model = glm::rotate(model, 100.f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, 
							glm::value_ptr(camera->calculateViewMatrix()));
		meshList[0]->Render();
		glUseProgram(0);
	
		mainWindow->swapBuffers();
	}
	

	// call free, change to smart pointers
	meshList[0]->Clear();
	return 0;
}