#include "ShaderProgram.h"
//#include "sphere.h"
#include <sstream>
GLfloat position[8 * 3] =
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
const GLfloat color[8 * 3] =
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
GLuint indices[12 * 3] =
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
GLfloat positionRect[4 * 2] =
{
	-1.0f, -1.0f,
	1.0f, -1.0f,
	-1.0f, 1.0f,
	1.0f, 1.0f
};
GLfloat texCoordRect[4 * 2] =
{
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f
};

ShaderProgram::ShaderProgram()
{

	glGenTextures(1, &color0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, color0);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, width, height, frame_layers, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
		glGenTextures(1, &depth);
	glBindTexture(GL_TEXTURE_2D_ARRAY, depth);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT, width, height, frame_layers, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, color0, 0);
	glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth, 0);
	glViewportIndexedf(1, 0.0, 0.0, static_cast<GLfloat>(1600), static_cast<GLfloat>(900));

	GLenum error = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if (error != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "framebuffer error:   " << error << std::endl;
	}
	else {
		std::cout << "framebuffer is complete" << std::endl;
	}

	
		program = glCreateProgram();
	glAttachShader(program, LoadShader(GL_VERTEX_SHADER, "shaders/rozmycie_ruchu_vs.glsl"));
	glAttachShader(program, LoadShader(GL_FRAGMENT_SHADER, "shaders/rozmycie_ruchu_smooth_fs.glsl"));
	glAttachShader(program, LoadShader(GL_GEOMETRY_SHADER, "shaders/rozmycie_ruchu_smooth_gs.glsl"));
	LinkValidateProgram(program);

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	
		glGenBuffers(1, &vertexBuffer1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glGenBuffers(1, &vertexBuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	
		glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &indicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);

	
		programRec = glCreateProgram();
	glAttachShader(programRec, LoadShader(GL_VERTEX_SHADER, "shaders/prostakat_vs.glsl"));
	glAttachShader(programRec, LoadShader(GL_FRAGMENT_SHADER, "shaders/prostakat_fs.glsl"));
	LinkValidateProgram(programRec);
	
		glGenVertexArrays(1, &vertexArrayRec);
	glBindVertexArray(vertexArrayRec);
	
		glGenBuffers(1, &vertexBufferRec1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferRec1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positionRect), positionRect, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	
		glGenBuffers(1, &vertexBufferRec2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferRec2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoordRect), texCoordRect, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);
	
		glBindVertexArray(0);

	

		glEnable(GL_DEPTH_TEST);

	GLenum err;
	if ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "OpenGL error: " << err << "line:" << std::endl;
	}
	else {
		std::cout << "jest ok" << std::endl;
	}
}
ShaderProgram::~ShaderProgram()
{
	//dtor
}

void ShaderProgram::render(glm::mat4x4 mvp) {

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);

	glEnable(GL_DEPTH_TEST);
	static double asdf= 0;

	asdf += glfwGetTime();
	mvp = glm::rotate(mvp, static_cast<GLfloat>(asdf*1.0), glm::vec3(1.0, 1.0, 1.0));
	mvp = glm::translate(mvp, glm::vec3(2.0f*sin(asdf)*1, 0.0, 0.0));
	std::cout << "asdasdsad" << std::endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int layer = 15; layer > 0; layer--) {
		modelViewMatrix[layer] = modelViewMatrix[layer - 1];
	}


	modelViewMatrix[0] = mvp;


	glBindVertexArray(vertexArray);

	glUseProgram(program);

	for (int layer = 0; layer < 16; layer++)
	{
		std::ostringstream txt;
		txt << "modelViewProjectionMatrix[" << layer << "]";
		glm::mat4x4 modelViewProjectionMatrix = modelViewMatrix[layer];
		glUniformMatrix4fv(glGetUniformLocation(program, txt.str().c_str()), 1, GL_FALSE, glm::value_ptr(modelViewProjectionMatrix));
	}

	glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, NULL);

	glUseProgram(0);

	glBindVertexArray(0);


	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glClearColor(1.0, 1.0, 1.0, 0.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D_ARRAY, color0);

	glBindVertexArray(vertexArrayRec);

	glUseProgram(programRec);

	glUniform1i(glGetUniformLocation(programRec, "tex"), 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);
	glUseProgram(0);

}
