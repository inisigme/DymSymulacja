#pragma once
#include "wszystko.h"
#include "Source.h"
#include <vector>
#include "View.h"
#include <ctime>
#include "Physics.h"

typedef struct Src {
public:
	unsigned int start;
	unsigned int end;
	glm::vec3 startPos;
	GLfloat range;
	GLfloat maxH;
	unsigned int noiseType;
	glm::vec3 smokeColor;
	GLfloat particleSize;
	glm::vec3 startVelocity;
	glm::vec3 startVelocityRange;
	GLfloat alpha;

	// Forces
	glm::vec3 gravity = glm::vec3(0.0, -9.8, 0.0);
	glm::vec3 wind;

	GLfloat temperature = 70.0;
	GLfloat mass = 0.1;

} Src;



class Emiter
{
public:
	std::vector<Src *> srcs;			// dane zrodel
	int count;															// ilosc czastek
	GLfloat *pos;												// [x,y,z,numer_tekstury,...]
	GLfloat *velocities;
	struct Src *sources;
	unsigned int sourcesCount;
	Emiter(std::vector<Src*>, unsigned int, unsigned int);

	void update(GLfloat);
	void draw(glm::mat4x4 MVPMatrix, View *view, GLuint program, GLuint);

	GLfloat noise1x(unsigned int i, unsigned int j, GLfloat);
	GLfloat noise1y(unsigned int i, unsigned int j, GLfloat);
	GLfloat noise1z(unsigned int i, unsigned int j, GLfloat);

	//	GLfloat noise1z(unsigned int i, unsigned int j);
	GLfloat noise2(unsigned int i, unsigned int j, GLfloat);

	~Emiter();
};

