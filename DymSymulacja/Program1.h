#pragma once
#include "wszystko.h"

class Program1
{
public:
	GLuint program;
	GLuint vertexBuffer[2];
	GLuint indicesBuffer;
	GLuint vertexArray;
	Program1();
	void render(glm::mat4x4 MVPMatrix);
	~Program1();
};

