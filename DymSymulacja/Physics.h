#pragma once

#include "wszystko.h"
#include <vector>

using glm::vec3;

class Physics
{
public:
	static const GLfloat constConv1;
	static const GLfloat constConv2;
	static const GLfloat constCooling;

	static glm::vec3 position(glm::vec3 position, GLfloat dTime, glm::vec3 velocity);
	static glm::vec3 velocity(glm::vec3 velocity, GLfloat dTime, glm::vec3 force, GLfloat mass);

	static glm::vec3 allForces();
	static vec3 force_gravitation(vec3 gravity, GLfloat mass);
	static vec3 force_convection(GLfloat temperature, GLfloat airTemperature);
	static vec3 force_friction();

	static GLfloat temperature(GLfloat temperature, GLfloat dTime, GLfloat airTemperature);

private:

};