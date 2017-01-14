#include "Emiter.h"
#include <ctime>


// zwezajacy sie
inline GLfloat Emiter::noise1x(unsigned int i, unsigned int j, GLfloat dTime) {
	//return 0.01f*sin(pos[j * 4 + 1]) + 0.1f* (srcs[i].startPos.x -pos[j*4 + 0] + pos[j * 4 + 1]);
	return rand() / (float)RAND_MAX / 10.0f -0.05 + (srcs[i].startPos.x - pos[j * 4 + 0]) / 400.f;
}
inline GLfloat Emiter::noise1y(unsigned int i, unsigned int j, GLfloat dTime) {
	return rand() / (float)RAND_MAX / 100.f - 0.002;
}
inline GLfloat Emiter::noise1z(unsigned int i, unsigned int j, GLfloat dTime) {
//	return 0.01f*sin(pos[j * 4 + 1]) + 0.1f* (srcs[i].startPos.z - pos[j * 4 + 2]+pos[j*4+1]);
	return rand() / (float)RAND_MAX / 10.f - 0.05 + (srcs[i].startPos.x - pos[j * 4 + 2]) / 400.f;
}


//do zewnatrz
inline GLfloat Emiter::noise2(unsigned int i, unsigned int j,GLfloat dTime) {


}


Emiter::~Emiter()
{
}


Emiter::Emiter(std::vector<Src> srcs, unsigned int count, unsigned int sourceCount)
{
	pos = new GLfloat[count*4];
	this->srcs = srcs;
	this->velocities = new GLfloat[count * 3];
	this->sourcesCount = sourceCount;
	this->count = count;
	for (int i = 0; i < sourceCount; i++) {
		glm::vec3 startPos = srcs[i].startPos;
		GLfloat range = srcs[i].range;
		GLfloat maxH = srcs[i].maxH;
		for (unsigned int j = srcs[i].start; j < srcs[i].end; j++) {
			velocities[j * 3 + 0] = srcs[i].startVelocity.x + rand()/(float)RAND_MAX * srcs[i].startVelocityRange.x;
			velocities[j * 3 + 1] = srcs[i].startVelocity.y + rand() / (float)RAND_MAX * srcs[i].startVelocityRange.y;
			velocities[j * 3 + 2] = srcs[i].startVelocity.z + rand() / (float)RAND_MAX * srcs[i].startVelocityRange.z;
			pos[j*4 + 0] = (rand() / (float)RAND_MAX - 0.5f) * range + startPos.x/100;
			pos[j*4 + 1] = (rand() / (float)RAND_MAX) * maxH ;
			pos[j*4 + 2] = (rand() / (float)RAND_MAX - 0.5f) * range + startPos.z/100;
			pos[j * 4 + 3] = (rand() / (float)RAND_MAX) * 6;
		}
	}

}

void Emiter::update(GLfloat dTime) {
	static GLfloat lastTime = 0;
	dTime -= lastTime;
	lastTime = glfwGetTime();
	for (int i = 0; i < this->sourcesCount; i++) {
		//int (Emiter::func1)(char, float);

		glm::vec3 startPos = srcs[i].startPos;
		GLfloat range = srcs[i].range;
		GLfloat maxH = srcs[i].maxH;
		glm::vec3 wind = srcs[i].wind;
		GLfloat gravity = srcs[i].gravity;
		for (int j = srcs[i].start; j < srcs[i].end; j++) {
			//pos[j * 4 + 1] += dTime * ( gravity + wind.y + noise1y(i, j, dTime));
			//pos[j * 4 + 0] += dTime * ( wind.x + noise1x(i,j, dTime) );
			//pos[j * 4 + 2] += dTime * ( wind.z + noise1z(i,j, dTime) );
			//LEPSZA WERSJA
			
			velocities[j * 3 + 0] += noise1x(i, j, dTime);
			velocities[j * 3 + 1] += noise1y(i, j, dTime);
			velocities[j * 3 + 2] += noise1z(i, j, dTime);
			pos[j * 4 + 0] += dTime * (velocities[j * 3 + 0] + wind.x);
			pos[j * 4 + 1] += dTime * (velocities[j * 3 + 1] + wind.y);
			pos[j * 4 + 2] += dTime * (velocities[j * 3 + 2] + wind.z);
			

			if (pos[j * 4 + 1] > maxH )
			{
				velocities[j * 3 + 0] = srcs[i].startVelocity.x + rand() / (float)RAND_MAX * srcs[i].startVelocityRange.x;
				velocities[j * 3 + 1] = srcs[i].startVelocity.y + rand() / (float)RAND_MAX * srcs[i].startVelocityRange.y;
				velocities[j * 3 + 2] = srcs[i].startVelocity.z + rand() / (float)RAND_MAX * srcs[i].startVelocityRange.z;
				pos[j*4 + 0] = (rand() / (float)RAND_MAX - 0.5f) * range + startPos.x ;
				pos[j*4 + 1] = (rand() / (float)RAND_MAX/10 ) *2 + startPos.y ;
				pos[j*4 + 2] = (rand() / (float)RAND_MAX - 0.5f) * range + startPos.z ;
				pos[j*4 + 3] = (rand() / (float)RAND_MAX) * 6;
			}
		}
	}
}


void Emiter::draw(glm::mat4x4 MVPMatrix, View *view, GLuint program) {
	ERR
		glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	for (int i = 0; i < sourcesCount; i++) {
		glm::vec3 dir = view->centers - view->eyes;
		glm::mat4x3 offests = glm::mat4x3();
		dir = glm::cross(dir, glm::vec3(0.0, 1.0, 0.0));
		dir = glm::normalize(dir);
		GLfloat wys = 1.f*srcs[i].particleSize;
		offests[0] = glm::vec3(dir.x*srcs[i].particleSize, -wys, dir.z*srcs[i].particleSize);
		offests[1] = glm::vec3(dir.x*srcs[i].particleSize, wys, dir.z*srcs[i].particleSize);
		offests[3] = glm::vec3(-dir.x*srcs[i].particleSize, wys, -dir.z*srcs[i].particleSize);
		offests[2] = glm::vec3(-dir.x*srcs[i].particleSize, -wys, -dir.z*srcs[i].particleSize);
		glm::vec3 kolorDymu = srcs[i].smokeColor;
		ERR
		glUniform3f(glGetUniformLocation(program, "kolorDymu"), kolorDymu.x, kolorDymu.y, kolorDymu.z);
		ERR
		glUniformMatrix4x3fv(glGetUniformLocation(program, "offsets"), 1, GL_FALSE, glm::value_ptr(offests));
		glUniform1f(glGetUniformLocation(program, "alpha"), srcs[i].alpha);
		glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(MVPMatrix));
		glUniform1f(glGetUniformLocation(program, "pointSize"), srcs[i].particleSize); ERR
		glDrawArrays(GL_POINTS, srcs[i].start, srcs[i].end - srcs[i].start);
	//	glDrawArrays(GL_POINTS,1000, 999);
	}
	glUseProgram(0); ERR
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	ERR
	
}