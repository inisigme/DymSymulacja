#include "System2.h"
#include <iomanip>
#include <glm/gtc/matrix_transform.hpp>
#include <sstream>

System2::System2()
{
	ERR
	std::vector <Src> vec;
	Src *s = new Src;
	s->maxH = 20.f;
	s->range = 2.f;
	s->start = 0;
	s->end = 400;
	s->startPos =	glm::vec3(10.f, 0.f, 10.f);
	s->wind = glm::vec3(0.00, 0.0, 0.0);
	s->gravity = 5.1f;
	s->smokeColor = glm::vec3(2.3, 2.3f,2.3);
	s->particleSize = 1;
	s->startVelocity = glm::vec3(0.0, 4, 0.0);
	s->startVelocityRange = glm::vec3(0.01,0.0,0.01);
	s->alpha = 0.005;
	vec.push_back(*s);

	Src *s4 = new Src;
	s4->maxH = 10.f;
	s4->range = 2.f;
	s4->start = 401;
	s4->end = 999;
	s4->startPos = glm::vec3(50.f, 0.f, 50.f);
	s4->wind = glm::vec3(8.00, 0.0,8.0);
	s4->gravity = 5.1f;
	s4->smokeColor = glm::vec3(0.05, 0.5f, 0.5);
	s4->particleSize = 1.4;
	s4->startVelocity = glm::vec3(3.0, 4, 3.0);
	s4->startVelocityRange = glm::vec3(12.01, 0.0, 12.01);
	s4->alpha = 0.01;
	vec.push_back(*s4);

	Src *s2 = new Src;
	s2->maxH = 50.f;
	s2->range = 6.f;
	s2->start = 1000;
	s2->end = 1999;
	s2->startPos = glm::vec3(20.f, 0.f, 20.f);
	s2->wind = glm::vec3(1.00, 0.0, 0.0);
	s2->gravity = 5.1f;
	s2->smokeColor = glm::vec3(1.0,0.f, 0.0);
	s2->particleSize = 1.9;
	s2->startVelocity = glm::vec3(0.0, 4, 0.0);
	s2->startVelocityRange = glm::vec3(8.01, 10.0, 8.01);
	s2->alpha = 0.018;
	vec.push_back(*s2);

	Src *s3 = new Src;
	s3->maxH = 30.f;
	s3->range = 0.f;
	s3->start = 2000;
	s3->end = 2999;
	s3->startPos = glm::vec3(40.f, 0.f, 40.f);
	s3->wind = glm::vec3(5.00, 0.0, 0.0);
	s3->gravity = 5.1f;
	s3->smokeColor = glm::vec3(1.0, 0.5f, 0.0);
	s3->particleSize = 1.3;
	s3->startVelocity = glm::vec3(0.0, 4, 0.0);
	s3->startVelocityRange = glm::vec3(8.01, 0.0, 8.01);
	s3->alpha = 0.003;
	vec.push_back(*s3);

	Src *s5 = new Src;
	s5->maxH = 20.f;
	s5->range = 2.f;
	s5->start = 3000;
	s5->end = 3499;
	s5->startPos = glm::vec3(00.f, 0.f, 10.f);
	s5->wind = glm::vec3(0.00, 0.0, 0.0);
	s5->gravity = 5.1f;
	s5->smokeColor = glm::vec3(0.15, 1.0f, 0.1);
	s5->particleSize = 1.2;
	s5->startVelocity = glm::vec3(0.0, 14, 0.0);
	s5->startVelocityRange = glm::vec3(10.01, 0.0, 10.01);
	s5->alpha = 0.005;
	vec.push_back(*s5);

	this->e = new Emiter(vec, 3500, 5);
	this->sky = new Skybox();
	this->s = new Swiat();
	glGenTextures(1, &texture23);
	glBindTexture(GL_TEXTURE_2D, texture23);
	ERR
	// wczytanie tekstury
	if (!LoadTexture("textures/tex1.jpg", GL_TEXTURE_2D))
	{
		std::cout << "Niepoprawny odczyt pliku " << std::endl;
		exit(0);
	}  
	ERR
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
//	u = new Uklad();
	prostokat = glCreateProgram();
	glAttachShader(prostokat, LoadShader(GL_VERTEX_SHADER, "shaders/prostakat_vs.glsl"));
//	glAttachShader(prostokat, LoadShader(GL_FRAGMENT_SHADER, "shaders/convolution_filters_3x3.glsl"));
	glAttachShader(prostokat, LoadShader(GL_FRAGMENT_SHADER, "shaders/prostakat_fs.glsl"));

	ERR
	LinkValidateProgram(prostokat); 
	GLfloat position23[4 * 2] =
	{
		-1.0f, -1.0f,
		1.0f, -1.0f,
		-1.0f, 1.0f,
		1.0f, 1.0f
	};

	GLfloat texCoord[4 * 2] =
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f
	};

	glGenVertexArrays(1, &vertexArrayR);
	glBindVertexArray(vertexArrayR);
	glGenBuffers(1, &vertexBuffer1R);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer1R);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position23), position23, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);


	glGenBuffers(1, &vertexBuffer2R);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer2R);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	ERR

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
	glUseProgram(0);

	//////////////////////////////

	glGenTextures(1, &color0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, color0);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, FRAME_WIDTH, FRAME_HEIGHT, frame_layers, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	ERR
	glGenTextures(1, &depth);
	glBindTexture(GL_TEXTURE_2D_ARRAY, depth);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT, FRAME_WIDTH, FRAME_HEIGHT, frame_layers, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, color0, 0);
	glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth, 0);
	glViewportIndexedf(1, 0.0, 0.0, static_cast<GLfloat>(FRAME_WIDTH), static_cast<GLfloat>(FRAME_HEIGHT));

	//////////////////



	GLenum error = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if (error != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "framebuffer error:   " << error << std::endl;
	}
	else {
		std::cout << "framebuffer is complete" << std::endl;
	}
	

	glClearColor(0.0f, 0.0f, 1.f, 1.0f);
	
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
	ERR
	const char *fileNames[6] =
	{
		"textures/test22.png",
		"textures/test22.png",
		"textures/test24.png",
		"textures/test22.png",
		"textures/test22.png",
		"textures/test24.png"
	};
	
	// wczytanie tekstur
	if (!LoadTextures(fileNames, GL_TEXTURE_2D_ARRAY, 6))
	{
		std::cout << "Niepoprawny odczyt pliku" << std::endl;
		exit(0);
	}
	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

	program = glCreateProgram();
	glAttachShader(program, LoadShader(GL_VERTEX_SHADER, "shaders/dym_vs.glsl"));
	glAttachShader(program, LoadShader(GL_GEOMETRY_SHADER, "shaders/dym_gs.glsl"));
	glAttachShader(program, LoadShader(GL_FRAGMENT_SHADER, "shaders/dym_fs.glsl"));
	LinkValidateProgram(program);

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, e->count*sizeof(GLfloat)*4, e->pos, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glEnable(GL_PROGRAM_POINT_SIZE);

	ERR
}

void System2::render(glm::mat4x4 MVPMatrix, View *view)
{
	
	
	modelViewMatrix[0] = MVPMatrix;
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ERR
		/*glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
			glClearColor(0.0, 0.0, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			u->render(MVPMatrix);*/
		ERR
		glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	s->render(MVPMatrix);
	sky->render(MVPMatrix);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquation(GL_FUNC_ADD);
	glDisable(GL_DEPTH_TEST);
	
	e->update((GLfloat)glfwGetTime());
	ERR
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	ERR
	glBufferSubData(GL_ARRAY_BUFFER, 0, e->count * sizeof(GLfloat)*4, e->pos);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
	glBindVertexArray(vertexArray); ERR
	glUseProgram(program); ERR
	glUniform1i(glGetUniformLocation(program, "tex"), 0);


	for (int layer = 0; layer < 1; layer++)
	{
		std::ostringstream txt;
		txt << "modelViewProjectionMatrix[" << layer << "]";
		glm::mat4x4 modelViewProjectionMatrix = modelViewMatrix[layer];
		glUniformMatrix4fv(glGetUniformLocation(program, txt.str().c_str()), 1, GL_FALSE, glm::value_ptr(modelViewProjectionMatrix));
	}
	e->draw(MVPMatrix, view, program);
	
	
	
	//glDisable(GL_POINT_SPRITE);

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);


	/*glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, FRAME_WIDTH, FRAME_HEIGHT,
		0, 0, FRAME_WIDTH, FRAME_HEIGHT,
		GL_COLOR_BUFFER_BIT, GL_LINEAR);
*/	
	/*glDisable(GL_BLEND);
	glm::mat4x4 p = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
	//glClearColor(0.0, 0.0, 0.0, 1.0);
	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ERR
		glBindTexture(GL_TEXTURE_2D, renderTexture[0]);
	ERR
		glBindVertexArray(vertexArrayR);
	ERR
		glUseProgram(prostokat);
	ERR
		glUniform1i(glGetUniformLocation(prostokat, "tex"), 0);
	ERR
	glUniform1i(glGetUniformLocation(program, "filterType"),1);
	ERR
		glUniformMatrix4fv(glGetUniformLocation(prostokat, "modelViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(p));
	ERR
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	ERR	
		glUseProgram(0);
	glBindVertexArray(0);*/

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D_ARRAY, color0);

	glBindVertexArray(vertexArrayR);

	glUseProgram(prostokat);

	glUniform1i(glGetUniformLocation(prostokat, "tex"),0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);
	glUseProgram(0);

}


System2::~System2()
{
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &vertexArray);
	glDeleteTextures(1, &texture);
}
