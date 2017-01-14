#pragma once
#include "wszystko.h"
#include <ctime>
#include "textures.h"
#define MAX_VERTEX 2000
class system1
{
public:
	GLfloat position[MAX_VERTEX * 4];
	GLuint program;
	GLuint vertexBuffer;
	GLuint indicesBuffer;
	GLuint vertexArray;
	GLuint texture;
	GLfloat szerokosc = 5.f;
	GLfloat wysokosc = 30.f;
	system1();
	void render(glm::mat4x4 MVPMatrix);
	~system1();
};

