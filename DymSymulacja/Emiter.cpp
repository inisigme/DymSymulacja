#include "Emiter.h"


// zwezajacy sie
inline GLfloat Emiter::noise1x(unsigned int i, unsigned int j, GLfloat dTime) {
	//return 0.01f*sin(pos[j * 4 + 1]) + 0.1f* (srcs[i].startPos.x -pos[j*4 + 0] + pos[j * 4 + 1]);
	return rand() / (float)RAND_MAX / 50.0f - 0.01;// +(srcs[i]->startPos.x - pos[j * 4 + 0]) / 400.f;
}
inline GLfloat Emiter::noise1y(unsigned int i, unsigned int j, GLfloat dTime) {
//	return rand() / (float)RAND_MAX / 100.f - 0.002;
	return 0;
}
inline GLfloat Emiter::noise1z(unsigned int i, unsigned int j, GLfloat dTime) {
	//	return 0.01f*sin(pos[j * 4 + 1]) + 0.1f* (srcs[i].startPos.z - pos[j * 4 + 2]+pos[j*4+1]);
	return rand() / (float)RAND_MAX / 50.f - 0.01;// +(srcs[i]->startPos.x - pos[j * 4 + 2]) / 400.f;
}


//do zewnatrz
inline GLfloat Emiter::noise2(unsigned int i, unsigned int j, GLfloat dTime) {


}


Emiter::~Emiter()
{
}


Emiter::Emiter(std::vector<Src *> srcs, unsigned int count, unsigned int sourceCount)
{
	pos = new GLfloat[count * 4];
	this->srcs = srcs;
	this->velocities = new GLfloat[count * 3];
	this->temperatures = new GLfloat[count];
	this->sourcesCount = sourceCount;
	this->count = count;
	for (int i = 0; i < sourceCount; i++) {
		glm::vec3 startPos = srcs[i]->startPos;
		GLfloat range = srcs[i]->range;
		GLfloat maxH = srcs[i]->maxH;
		for (unsigned int j = srcs[i]->start; j < srcs[i]->end; j++) {
			velocities[j * 3 + 0] = srcs[i]->startVelocity.x + rand() / (float)RAND_MAX * srcs[i]->startVelocityRange.x;
			velocities[j * 3 + 1] = srcs[i]->startVelocity.y + rand() / (float)RAND_MAX * srcs[i]->startVelocityRange.y;
			velocities[j * 3 + 2] = srcs[i]->startVelocity.z + rand() / (float)RAND_MAX * srcs[i]->startVelocityRange.z;
			pos[j * 4 + 0] = (rand() / (float)RAND_MAX - 0.5f) * range + startPos.x / 100;
			pos[j * 4 + 1] = (rand() / (float)RAND_MAX) * maxH;
			pos[j * 4 + 2] = (rand() / (float)RAND_MAX - 0.5f) * range + startPos.z / 100;
			pos[j * 4 + 3] = (rand() / (float)RAND_MAX) * 6;
			temperatures[j] = srcs[i]->temperature;
		}
	}
}

void Emiter::update(GLfloat currentTime) {
	static GLfloat lastTime = 0;
	GLfloat dTime = currentTime - lastTime;
	lastTime = glfwGetTime();
	for (int i = 0; i < this->sourcesCount; i++) {

		glm::vec3 startPos = srcs[i]->startPos;
		GLfloat range = srcs[i]->range;
		GLfloat maxH = srcs[i]->maxH;
		glm::vec3 wind = srcs[i]->wind;
		glm::vec3 gravity = srcs[i]->gravity;
		for (int j = srcs[i]->start; j < srcs[i]->end; j++) {

			glm::vec3 force_convection = Physics::force_convection(temperatures[j], srcs[i]->airTemperature);

			glm::vec3 force = Physics::force_gravitation(gravity, srcs[i]->mass) + force_convection + wind;

			glm::vec3 velocity = glm::vec3(velocities[j * 3 + 0], velocities[j * 3 + 1], velocities[j * 3 + 2]);
			velocity = Physics::velocity(velocity, dTime, force, srcs[i]->mass);

			glm::vec3 position = glm::vec3(pos[j * 4 + 0], pos[j * 4 + 1], pos[j * 4 + 2]);
			position = Physics::position(position, dTime, velocity);

			velocities[j * 3 + 0] = velocity.x;
			velocities[j * 3 + 1] = velocity.y;
			velocities[j * 3 + 2] = velocity.z;
			pos[j * 4 + 0] = position.x + noise1x(i, j, dTime);
			pos[j * 4 + 1] = position.y + noise1y(i, j, dTime);
			pos[j * 4 + 2] = position.z + noise1z(i, j, dTime);

			if (glm::distance(srcs[i]->startPos, position) > maxH) // znika jesli zbyt daleko od zrodla
			{
				velocities[j * 3 + 0] = srcs[i]->startVelocity.x + rand() / (float)RAND_MAX * srcs[i]->startVelocityRange.x;
				velocities[j * 3 + 1] = srcs[i]->startVelocity.y + rand() / (float)RAND_MAX * srcs[i]->startVelocityRange.y;
				velocities[j * 3 + 2] = srcs[i]->startVelocity.z + rand() / (float)RAND_MAX * srcs[i]->startVelocityRange.z;
				pos[j * 4 + 0] = (rand() / (float)RAND_MAX - 0.5f) * range + startPos.x;
				pos[j * 4 + 1] = (rand() / (float)RAND_MAX / 10) * 2 + startPos.y;
				pos[j * 4 + 2] = (rand() / (float)RAND_MAX - 0.5f) * range + startPos.z;
				pos[j * 4 + 3] = (rand() / (float)RAND_MAX) * 6;
				temperatures[j] = srcs[i]->temperature;
			}
		}
	}
}


void Emiter::draw(glm::mat4x4 MVPMatrix, View *view, GLuint program, GLuint asd) {
	ERR
		glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	for (int i = 0; i < sourcesCount; i++) {
		glm::vec3 dir = view->centers - view->eyes;
		glm::mat4x3 offests = glm::mat4x3();
		dir = glm::cross(dir, glm::vec3(0.0, 1.0, 0.0));
		dir = glm::normalize(dir);
		GLfloat wys = 1.f*srcs[i]->particleSize;
		offests[0] = glm::vec3(dir.x*srcs[i]->particleSize, -wys, dir.z*srcs[i]->particleSize);
		offests[1] = glm::vec3(dir.x*srcs[i]->particleSize, wys, dir.z*srcs[i]->particleSize);
		offests[3] = glm::vec3(-dir.x*srcs[i]->particleSize, wys, -dir.z*srcs[i]->particleSize);
		offests[2] = glm::vec3(-dir.x*srcs[i]->particleSize, -wys, -dir.z*srcs[i]->particleSize);
		glm::vec3 kolorDymu = srcs[i]->smokeColor;
		ERR
			glUniform3f(glGetUniformLocation(program, "kolorDymu"), kolorDymu.x, kolorDymu.y, kolorDymu.z);
		ERR
			glUniformMatrix4x3fv(glGetUniformLocation(program, "offsets"), 1, GL_FALSE, glm::value_ptr(offests));
		glUniform1f(glGetUniformLocation(program, "alpha"), srcs[i]->alpha);
		glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(MVPMatrix));
		glUniform1f(glGetUniformLocation(program, "pointSize"), srcs[i]->particleSize); ERR
			glDrawArrays(GL_POINTS, srcs[i]->start, srcs[i]->end - srcs[i]->start);
		//	glDrawArrays(GL_POINTS,1000, 999);
	}
	glUseProgram(0); ERR
		glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	ERR

}