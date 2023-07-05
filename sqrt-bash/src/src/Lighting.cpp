#include "Lighting.h"

Light::Light()
{
	color = glm::vec3(1.f, 1.f, 1.f);
	ambientIntensity = 1.f;

}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity)
{
	color = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
}

Light::~Light()
{
}

void Light::Use(GLuint ambientIntensityLoc, GLuint ambientColorLoc)
{
	glUniform3f(ambientColorLoc, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLoc, ambientIntensity);
}

Diffuse::Diffuse() {
	Light();

	direction = glm::vec3(0.f, -1.f, 0.f);
	diffuseIntensity = 0.f;
}

Diffuse::Diffuse(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
					GLfloat x, GLfloat y, GLfloat z, GLfloat dIntensity) {
	Light::Light(red, green, blue, aIntensity);
	
	direction = glm::vec3(x, y, z);
	diffuseIntensity = dIntensity;
}

Diffuse::~Diffuse() {

}

void Diffuse::Use(GLuint ambientIntensityLoc, GLfloat ambientColorLoc,
					GLfloat diffuseIntensityLoc, GLfloat directionLocation) {
	Light::Use(ambientIntensityLoc, ambientColorLoc);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLoc, diffuseIntensity);
}


