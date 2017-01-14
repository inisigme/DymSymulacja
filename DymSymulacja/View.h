#pragma once
#include "wszystko.h"
class View
{
public:
	View();
	~View();

	glm::mat4x4		view;
	glm::mat4x4		projection;
	glm::mat4x4		MVPMatrix;
	
	glm::vec3 eyes		= glm::vec3( -18.0, 9.5, 84.0);
	glm::vec3 centers	= glm::vec3( 100.0, 42.5, -32.0);
	glm::vec3 up		= glm::vec3(0.0, 1.0, 0.0);
	
	GLfloat	distance	= 0.5f;
	GLfloat	angle		= .2f;


	void stepFoward();
	void stepBack();
	void rotateHorizontal( GLfloat);
	void rotateVertical( GLfloat);
	
	void setDistance(GLfloat);
	void setAngle(GLfloat);
};

