#include "Swiat.h"
#include "parsowanie.h"


Swiat::Swiat()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if (!LoadTexture("textures/blackWall.jpg", GL_TEXTURE_2D))
	{

		exit(0);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	GLint internalFormat;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);
	if (internalFormat == GL_RED)
	{
		GLint swizzle[4] = { GL_RED, GL_RED, GL_RED, GL_ALPHA };
		glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzle);
	}

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);



	glBindVertexArray(0);
	program = glCreateProgram();
	glAttachShader(program, LoadShader(GL_VERTEX_SHADER, "shaders/swiat_vs.glsl"));
	glAttachShader(program, LoadShader(GL_GEOMETRY_SHADER, "shaders/swiat_gs.glsl"));
	glAttachShader(program, LoadShader(GL_FRAGMENT_SHADER, "shaders/swiat_fs.glsl"));
	LinkValidateProgram(program);

	vertexArray = parsowanie("trzySciany.obj");
	


}


Swiat::~Swiat()
{
}

void Swiat::render(glm::mat4x4 MVP, GLuint frame_layers) {
	glDisable(GL_BLEND);
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D); ERR
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	ERR
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindVertexArray(vertexArray);
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(MVP));
	glUniform1i(glGetUniformLocation(program, "tex"),1	);
	glDrawArrays(GL_TRIANGLES, 0, 3*4*6);
	glUseProgram(0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
}
