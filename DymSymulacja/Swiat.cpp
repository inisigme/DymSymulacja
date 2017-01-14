#include "Swiat.h"



Swiat::Swiat()
{
	program = glCreateProgram();
	glAttachShader(program, LoadShader(GL_VERTEX_SHADER, "shaders/swiat_vs.glsl"));
	glAttachShader(program, LoadShader(GL_GEOMETRY_SHADER, "shaders/swiat_gs.glsl"));
	glAttachShader(program, LoadShader(GL_FRAGMENT_SHADER, "shaders/swiat_fs.glsl"));
	LinkValidateProgram(program);

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glGenBuffers(1, &vertexBuffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glGenBuffers(1, &vertexBuffer[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);


	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glGenTextures(1, &texture);
	
	LoadTexture("textures/podloga.jpg", GL_TEXTURE_2D);
	//LoadTexture("textures/posx.jpg", GL_TEXTURE_2D);

	glGenerateMipmap(GL_TEXTURE_2D);
	ERR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	ERR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	ERR
		GLint internalFormat;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);
	if (internalFormat == GL_RED)
	{
		GLint swizzle[4] = { GL_RED, GL_RED, GL_RED, GL_ALPHA };
		glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzle);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	ERR

}


Swiat::~Swiat()
{
}

void Swiat::render(glm::mat4x4 MVP) {
	glFlush();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindVertexArray(vertexArray);
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(MVP));
	glUniform1i(glGetUniformLocation(program, "tex"),4	);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glUseProgram(0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
