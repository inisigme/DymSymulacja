#pragma once
#include "wszystko.h"


class Uklad
{
public:
	GLuint program;
	GLuint vertexBuffer[2];

	GLuint indicesBuffer;

	GLuint vertexArray;


	void render(glm::mat4x4);
	Uklad();
	~Uklad();
};

