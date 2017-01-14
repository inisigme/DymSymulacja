#pragma once
#include "wszystko.h"


class Krzyzyk
{
public:
	GLuint program;
	GLuint vertexBuffer[2];

	GLuint indicesBuffer;

	GLuint vertexArray;


	void render(glm::mat4x4, glm::vec3);
	Krzyzyk();
	~Krzyzyk();
};

