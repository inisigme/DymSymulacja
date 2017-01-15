#pragma once
#include "wszystko.h"
#include "textures.h"
class Swiat
{
	GLuint program, indicesBuffer, vertexArray, texture;
	GLuint vertexBuffer[2];

public:GLfloat position[3*4] =
{
	-20.f, -20.0, 10.0,
	20.f, -20.0, 10.0,
	-20.f, 20.0, 10.0,
	20.f, 20.0, 10.0,
};

	   const GLfloat texCoord[4 * 2] =
	   {
		   0.0, 0.0,
		   1, 0.0,
		   0.0,1,
		   1, 1,
	   };

	   void render(glm::mat4x4, GLuint);
	   Swiat();
	   ~Swiat();
};

