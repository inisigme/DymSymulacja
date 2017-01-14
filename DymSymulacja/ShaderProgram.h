#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include "wszystko.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const int frame_layers = 16;

class ShaderProgram
{
public:
	glm::mat4x4 modelViewMatrix[frame_layers];
	GLuint program;
	GLuint indicesBuffer;
	GLuint vertexArray;
	GLuint vertexBuffer1, vertexBuffer2;
	GLuint fbo, color0, color1, depth;
	GLuint programRec, vertexArrayRec, vertexBufferRec1, vertexBufferRec2;
	int width = 1600;
	int height = 900;
	ShaderProgram();
	virtual ~ShaderProgram();
	void render(glm::mat4x4 mvp);
protected:

private:
};

#endif // SHADERPROGRAM_H
