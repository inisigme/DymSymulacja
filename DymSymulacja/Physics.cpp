#include "Physics.h"

using glm::vec3;



const GLfloat Physics::constConv1  = 100;
const GLfloat Physics::constConv2  = 100;
const GLfloat Physics::constCooling = -1;

vec3 Physics::position(vec3 position, GLfloat dTime, vec3 velocity) {
	return position + (velocity * dTime);
}
vec3 Physics::velocity(vec3 velocity, GLfloat dTime, vec3 force, GLfloat mass) {
	return velocity + (force * dTime / mass);
}

vec3 Physics::allForces() {
	return vec3(0, 0, 0);
}
vec3 Physics::force_gravitation(vec3 gravity, GLfloat mass) {
	return gravity * mass;
}
vec3 Physics::force_convection(GLfloat temperature, GLfloat airtemperature) {
	return vec3(0.0,
			Physics::constConv1 / (abs(airtemperature) < 1 ? 1 : airtemperature) - Physics::constConv2 / (abs(temperature) < 1 ? 1 : temperature),
			0.0);
}

GLfloat Physics::temperature(GLfloat temperature, GLfloat dTime, GLfloat airTemperature) {
	return (temperature - airTemperature) * pow(exp(1), -dTime / Physics::constCooling) + airTemperature;
}

