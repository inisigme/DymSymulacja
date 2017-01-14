#include "Program1.h"

static GLfloat position[8 * 3] =
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

static const GLfloat color[8 * 3] =
{
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

static GLuint indices[12 * 3] =
{
	5, 1, 0,
	5, 0, 4,
	2, 3, 0,
	2, 0, 1,
	7, 4, 0,
	7, 0, 3,
	3, 2, 6,
	3, 6, 7,
	1, 6, 2,
	1, 5, 6,
	4, 6, 5,
	4, 7, 6
};


Program1::Program1()
{ 

	program = glCreateProgram();
	glAttachShader(program, LoadShader(GL_VERTEX_SHADER, "shaders/szescian_rgb_smooth_vs.glsl"));
	glAttachShader(program, LoadShader(GL_FRAGMENT_SHADER, "shaders/szescian_rgb_smooth_fs.glsl"));
	LinkValidateProgram(program);

	glGenVertexArrays(1, &vertexArray);

	glBindVertexArray(vertexArray);

	glGenBuffers(1, &vertexBuffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glGenBuffers(1, &vertexBuffer[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &indicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	// w��czenie testu bufora g��boko�ci
	glEnable(GL_DEPTH_TEST);
}

void Program1::render(glm::mat4x4 MVPMatrix)
{
	glBindVertexArray(vertexArray);
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(MVPMatrix));
	glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, NULL);
	glUseProgram(0);
	glBindVertexArray(0);
}


Program1::~Program1()
{
	glDeleteProgram(program);
	glDeleteBuffers(2, vertexBuffer);
	glDeleteBuffers(1, &indicesBuffer);
	glDeleteVertexArrays(1, &vertexArray);
}
