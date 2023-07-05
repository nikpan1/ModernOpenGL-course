#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

class Shader
{
public:
	Shader();
	~Shader();
	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFile(const char* vertexLocation, const char* fragmentLocation);
	
	std::string ReadFile(const char* FileLocation);

	void Use();
	void Clear();

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColorLocation();

	GLuint GetDiffusionIntensityLocation();
	GLuint GetDirectionLocation();

	GLuint GetSpecularDensityLocation();
	GLuint GetShininessLocation();
	
	GLuint GetEyePosition();

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView,
		uniformAmbientIntensity, uniformAmbientColor,
		uniformDiffuseIntensity, uniformDirection,
		uniformEyePosition, uniformSpecularIntensity, uniformShininess;
	void Compile(const char* vertexCode, const char* fragmentCode);
	void Add(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};
