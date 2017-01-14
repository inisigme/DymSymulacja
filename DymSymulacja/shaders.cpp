#define GLEW_STATIC 
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "shaders.h"

GLuint LoadShader(const GLenum type, const char *name)
{
	std::ifstream file;
	file.open(name, std::ios::binary);
	if (file.bad())
		exit(1234214);
	
	file.seekg(0, std::ios::end);
	int len = static_cast<int>(file.tellg());
	if (len <= 0)
		exit(436436);
	
	file.seekg(0, std::ios::beg);
	GLchar *srcBuf = new GLchar[(len + 1) * sizeof(GLchar)];
	file.read(srcBuf, len);
	srcBuf[len] = '\0';
	file.close();

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, const_cast<const GLchar**>(&srcBuf), NULL);
	delete[] srcBuf;
	glCompileShader(shader);
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		std::cout << "Niepoprawna kompilacja shadera " << name << std::endl;
		GLint logLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		char *log = new char[logLength];
		glGetShaderInfoLog(shader, logLength, NULL, log);
		std::cout << log << std::endl;
		delete[] log;
		getchar();
		exit(0);
	}
	return shader;
}

void LinkValidateProgram(GLuint program)
{
	glLinkProgram(program);
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::cout << "Niepoprawna konsolidacja programu" << std::endl;
		GLint logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		char *log = new char[logLength];
		glGetProgramInfoLog(program, logLength, NULL, log);
		std::cout << log << std::endl;
		delete[] log;
		getchar();
		exit(0);
	}
	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::cout << "Niepoprawna walidacja programu" << std::endl;
		GLint logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		char *log = new char[logLength];
		glGetProgramInfoLog(program, logLength, NULL, log);
		std::cout << log << std::endl;
		delete[] log;
		getchar();
		exit(0);
	}
}
