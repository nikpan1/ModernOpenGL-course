#pragma once

#include "Lighting.h"

class PointLight : public Light {

public:

	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue,
				GLfloat aIntensity, GLfloat dIntensity,
				GLfloat x, GLfloat y, GLfloat z,
				GLfloat con, GLfloat lin, GLfloat exp);
	~PointLight();
	
	void Use(GLuint ambientIntensityLoc, GLfloat ambientColorLoc,
				GLfloat diffuseIntensityLoc, GLfloat directionLocation,
				GLfloat conLoc, GLfloat linLoc, GLfloat exp);


private:
	glm::vec3 position;
	GLfloat constant, linear, exponent; 

};
