#include "system1.h"
#include <iomanip>


system1::system1()
{
	glClearColor(0.0f, 0.0f, 0.545098f, 1.0f);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
	
	const char *fileNames[6] =
	{
		"textures/tex1.jpg",
		"textures/tex1.jpg",
		"textures/tex1.jpg",
		"textures/tex1.jpg",
		"textures/tex1.jpg",
		"textures/tex1.jpg"
	};
	for (GLenum err; (err = glGetError()) != GL_NO_ERROR;)
	{
		std::cout << "1     " << err << std::endl;
	}

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
	glAttachShader(program, LoadShader(GL_VERTEX_SHADER, "shaders/snieg_vs.glsl"));
	glAttachShader(program, LoadShader(GL_FRAGMENT_SHADER, "shaders/snieg_fs.glsl"));
	LinkValidateProgram(program);
	
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	
	srand(static_cast<unsigned int>(time(NULL)));

	for (int i = 0; i < MAX_VERTEX; i++)
	{
		position[i * 4 + 0] = (rand()	/ (float)RAND_MAX) * (szerokosc *2) ;
		position[i * 4 + 1] = (rand()	/ (float)RAND_MAX) * (wysokosc) ;
		position[i * 4 + 2] = (rand()	/ (float)RAND_MAX) * (szerokosc * 2) ;

		position[i * 4 + 3] = (rand() / (float)RAND_MAX) * 6;
	}
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_DEPTH_TEST);

	for (GLenum err; (err = glGetError()) != GL_NO_ERROR;)
	{
		std::cout <<  err << std::endl;
	}
}

void system1::render(glm::mat4x4 MVPMatrix)
{
	glEnable(GL_POINT_SPRITE);


	for (int i = 0; i < 2000; i++)
	{
		position[i * 4 + 1] += 0.01f + rand() / (float)RAND_MAX * 0.01f;
		position[i * 4 + 0] += 0.003f * sin(position[i * 3 + 1]);
		position[i * 4 + 2] += 0.003f * cos(position[i * 3 + 1]);

		if (position[i * 4 + 1] > 20)
		{
			position[i * 4 + 0] = (rand() / (float)RAND_MAX) * (szerokosc * 2);
			position[i * 4 + 1] = 0.f;
			position[i * 4 + 2] = (rand() / (float)RAND_MAX) * (szerokosc * 2);

			position[i * 4 + 3] = (rand() / (float)RAND_MAX) * 6;
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 1000 * sizeof(GLfloat), position);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
	glBindVertexArray(vertexArray);
	glUseProgram(program);
	glUniform1i(glGetUniformLocation(program, "tex"), 0);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(MVPMatrix));
	glUniform1f(glGetUniformLocation(program, "pointSize"), 10.0);
	glDrawArrays(GL_POINTS, 0, 2000);
	glUseProgram(0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	for (GLenum err; (err = glGetError()) != GL_NO_ERROR;)
	{
		std::cout << err << std::endl;
	}
}


system1::~system1()
{
	glDeleteProgram(program);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vertexArray);
	glDeleteTextures(1, &texture);
}
