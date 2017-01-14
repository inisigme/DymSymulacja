#include "Krzyzyk.h"


static GLfloat position2[6 * 3] =
{
	-10000.0, 0.0, 0.0,
	1000.0, 0.0, 0.0,
	0.0f, -1000.0f, 0.0f,
	0.0f, 1000.0f, 0.0f,
	0.0f, 0.0f, 1000.0f,
	0.0f, 0.0f, -1000.0f
};

static const GLfloat color2[6 * 3] =
{
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	.0f, 1.0f, 1.0f,
	.0f, 1.0f, 1.0f
};

static GLuint indices2[8] =
{
	0,1,2,3,4,5
};

Krzyzyk::Krzyzyk()
{
	program = glCreateProgram();
	glAttachShader(program, LoadShader(GL_VERTEX_SHADER, "shaders/szescian_rgb_smooth_vs.glsl"));
	glAttachShader(program, LoadShader(GL_FRAGMENT_SHADER, "shaders/szescian_rgb_smooth_fs.glsl"));
	LinkValidateProgram(program);

	glGenVertexArrays(1, &vertexArray);

	glBindVertexArray(vertexArray);

	glGenBuffers(1, &vertexBuffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position2), position2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glGenBuffers(1, &vertexBuffer[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color2), color2, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &indicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);

}


void Krzyzyk::render(glm::mat4x4 MVPMatrix, glm::vec3 centers) {



	position2[1] = position2[4] = position2[13] = position2[16] = centers.y;
	position2[6] = position2[9] = position2[12] = position2[15] = centers.x;
	position2[2] = position2[5] = position2[8] = position2[11] = centers.z;


	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 6*3 * sizeof(GLfloat), position2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(vertexArray);
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(MVPMatrix));
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, NULL);
	glUseProgram(0);
	glBindVertexArray(0);
}

Krzyzyk::~Krzyzyk()
{
}
