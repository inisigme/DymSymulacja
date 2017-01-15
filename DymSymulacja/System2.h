#pragma once
#include "wszystko.h"
#include <ctime>
#include "textures.h"
#include "View.h"
#include "symulacja.h"
#include "Emiter.h"
#include <vector>
#include "Skybox.h"
#include "Swiat.h"
#define MAX_VERTEX 2000

#include "Uklad.h"

class System2
{
public:
	enum
	{
		POSITION,
		TEX_COORD,
		VERTEX_BUFFER_SIZE
	};
	GLuint asdf;
	GLuint frameBuffer;
	const int FRAME_WIDTH = 1200;
	const int FRAME_HEIGHT = 800;
	int frame_layers = 1; // DO ROZMUCIA RUCHU
	GLuint color0, depth, fbo;
	glm::mat4x4 modelViewMatrix[1];
	enum
	{
		COLOR0,
		DEPTH,
		RENDER_TEXTURE_SIZE
	}; 
	Skybox *sky;
	Emiter *e;
	Uklad *u;
	Swiat *s;
	GLuint prostokat;
	GLuint vertexArrayR, vertexBuffer1R, vertexBuffer2R;
	GLuint renderTexture[RENDER_TEXTURE_SIZE];
	GLuint program, texture23;
	GLuint vertexBuffer;
	GLuint indicesBuffer;
	GLuint vertexArray;
	GLuint texture;
	System2(Src *);
	void render(glm::mat4x4 MVPMatrix, View *view);
	~System2();
};

