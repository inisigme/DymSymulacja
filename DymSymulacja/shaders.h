#ifndef __SHADERS__H__
#define __SHADERS__H__

#include <GL/glew.h>

GLuint LoadShader(const GLenum type, const char *name);
void LinkValidateProgram(GLuint program);

#endif 
