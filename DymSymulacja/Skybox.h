#pragma once
#include "wszystko.h"
class Skybox
{
	GLuint program, indicesBuffer, vertexArray, texture;
	GLuint vertexBuffer[2];

	public:GLfloat position[8 * 3] =
		{
	2000.0f, 2000.0f, 2000.0f,
	-2000.0f, 2000.0f, 2000.0f,
	-2000.0f, -2000.0f, 2000.0f,
	2000.0f, -2000.0f, 2000.0f,
	2000.0f, 2000.0f, -2000.0f,
	-2000.0f, 2000.0f, -2000.0f,
	-2000.0f, -2000.0f, -2000.0f,
	2000.0f, -2000.0f, -2000.0f
};
	   
	const GLfloat texCoord[8 * 3] =
	   {
		   1.0f, 1.0f, 1.0f,
		   -1.0f, 1.0f, 1.0f,
		   -1.0f, -1.0f, 1.0f,
		   1.0f, -1.0f, 1.0f,
		   1.0f, 1.0f, -1.0f,
		   -1.0f, 1.0f, -1.0f,
		   -1.0f, -1.0f, -1.0f,
		   1.0f, -1.0f, -1.0f
	   };

	GLuint indices[12 * 3] =
	   {
		   5, 0, 1,
		   5, 4, 0,
		   2, 0, 3,
		   2, 1, 0,
		   7, 0, 4,
		   7, 3, 0,
		   3, 6, 2,
		   3, 7, 6,
		   1, 2, 6,
		   1, 6, 5,
		   4, 5, 6,
		   4, 6, 7
	   };
	void render(glm::mat4x4);
	Skybox();
	~Skybox();
};

