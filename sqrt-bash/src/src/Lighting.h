#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

// ambient lighting
class Light {
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity);
	~Light();

	void Use(GLuint ambientIntensityLoc, GLuint ambientColorLoc);

private:
	glm::vec3 color;
	GLfloat ambientIntensity;
};


// diffuse lighting / directional light
// phong interpolation

class Diffuse : Light {
public:
	Diffuse();
	Diffuse(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
				GLfloat x, GLfloat y, GLfloat z, GLfloat dIntensity);

	~Diffuse();

	void Use(GLuint ambientIntensityLoc, GLfloat ambienColorLoc, 
				GLfloat diffuseIntensityLoc, GLfloat directionLocation);

private:
	glm::vec3 direction;
	GLfloat diffuseIntensity;

};

