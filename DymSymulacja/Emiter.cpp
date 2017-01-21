#include "Emiter.h"

// zwezajacy sie
inline GLfloat Emiter::noise1x(unsigned int i, unsigned int j, GLfloat dTime)
{
  //return 0.01f*sin(pos[j * 4 + 1]) + 0.1f* (srcs[i].startPos.x -pos[j*4 + 0] + pos[j * 4 + 1]);
  return rand() / (float)RAND_MAX / 50.0f - 0.01; // +(srcs[i]->startPos.x - pos[j * 4 + 0]) / 400.f;
}
inline GLfloat Emiter::noise1y(unsigned int i, unsigned int j, GLfloat dTime)
{
  //	return rand() / (float)RAND_MAX / 100.f - 0.002;
  return 0;
}
inline GLfloat Emiter::noise1z(unsigned int i, unsigned int j, GLfloat dTime)
{
  //	return 0.01f*sin(pos[j * 4 + 1]) + 0.1f* (srcs[i].startPos.z - pos[j * 4 + 2]+pos[j*4+1]);
  return rand() / (float)RAND_MAX / 50.f - 0.01; // +(srcs[i]->startPos.x - pos[j * 4 + 2]) / 400.f;
}

//do zewnatrz
inline GLfloat Emiter::noise2(unsigned int i, unsigned int j, GLfloat dTime)
{
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
  for (int i = 0; i < sourceCount; i++)
  {
				Src *source = srcs[i];
    glm::vec3 startPos = source->startPos;
    GLfloat range = source->range;
    GLfloat maxH = source->maxH;
    for (unsigned int j = source->start; j < source->end; j++)
    {
						GLfloat *velo_x = &velocities[j * 3 + 0];
						GLfloat *velo_y = &velocities[j * 3 + 1];
						GLfloat *velo_z = &velocities[j * 3 + 2];
						GLfloat *pos_x = &pos[j * 4 + 0];
						GLfloat *pos_y = &pos[j * 4 + 1];
						GLfloat *pos_z = &pos[j * 4 + 2];
						GLfloat *texture = &pos[j * 4 + 3];
						GLfloat *temperature = &temperatures[j];

      *velo_x = source->startVelocity.x + rand() / (float)RAND_MAX * source->startVelocityRange.x;
      *velo_y = source->startVelocity.y + rand() / (float)RAND_MAX * source->startVelocityRange.y;
      *velo_z = source->startVelocity.z + rand() / (float)RAND_MAX * source->startVelocityRange.z;
      *pos_x = (rand() / (float)RAND_MAX - 0.5f) * range + startPos.x / 100;
      *pos_y = (rand() / (float)RAND_MAX) * maxH;
      *pos_z = (rand() / (float)RAND_MAX - 0.5f) * range + startPos.z / 100;
      *texture = (rand() / (float)RAND_MAX) * 6;
      *temperature = source->temperature;
    }
  }
}

void Emiter::update(GLfloat currentTime)
{
  static GLfloat lastTime = 0;
  GLfloat dTime = currentTime - lastTime;
  lastTime = glfwGetTime();
  for (int i = 0; i < this->sourcesCount; i++)
  {
				Src *source = srcs[i];
		
				glm::vec3 force_convection_respawn = Physics::force_convection(source->temperature, source->airTemperature);

    glm::vec3 startPos = source->startPos;
    GLfloat range = source->range;
    GLfloat maxH = source->maxH;
    glm::vec3 wind = source->wind;
    glm::vec3 gravity = source->gravity;

    for (int j = source->start; j < source->end; j++)
    {

						GLfloat *velo_x = &velocities[j * 3 + 0];
						GLfloat *velo_y = &velocities[j * 3 + 1];
						GLfloat *velo_z = &velocities[j * 3 + 2];

						GLfloat *pos_x = &pos[j * 4 + 0];
						GLfloat *pos_y = &pos[j * 4 + 1];
						GLfloat *pos_z = &pos[j * 4 + 2];

						GLfloat *texture = &pos[j * 4 + 3];

						GLfloat *temperature = &temperatures[j];

						if (j == source->start + 1000) std::cout << "Particle temperature is:\t" << *temperature << std::endl;


						glm::vec3 force_convection = Physics::force_convection(*temperature, source->airTemperature);

      glm::vec3 force = Physics::force_gravitation(gravity, source->mass) + force_convection + wind;

      glm::vec3 velocity = glm::vec3(*velo_x, *velo_y, *velo_z);
      velocity = Physics::velocity(velocity, dTime, force, source->mass);

						glm::vec3 position = glm::vec3(*pos_x, *pos_y, *pos_z);
      position = Physics::position(position, dTime, velocity);

						*temperature = Physics::temperature(*temperature, dTime, source->airTemperature);

						*velo_x = velocity.x;
						*velo_y = velocity.y;
						*velo_z = velocity.z;

						*pos_x = position.x + noise1x(i, j, dTime);
						*pos_y = position.y + noise1y(i, j, dTime);
						*pos_z = position.z + noise1z(i, j, dTime);

      if (glm::distance(source->startPos, position) > maxH) // znika jesli zbyt daleko od zrodla
      {
								*velo_x = force_convection_respawn.x + source->startVelocity.x + rand() / (float)RAND_MAX * source->startVelocityRange.x;
								*velo_y = force_convection_respawn.y + source->startVelocity.y + rand() / (float)RAND_MAX * source->startVelocityRange.y;
								*velo_z = force_convection_respawn.z + source->startVelocity.z + rand() / (float)RAND_MAX * source->startVelocityRange.z;
								*pos_x = (rand() / (float)RAND_MAX - 0.5f) * range + startPos.x;
								*pos_y = (rand() / (float)RAND_MAX / 10) * 2 + startPos.y;
								*pos_z = (rand() / (float)RAND_MAX - 0.5f) * range + startPos.z;
								*texture = (rand() / (float)RAND_MAX) * 6;
								*temperature = source->temperature;
      }
    }
  }
}

void Emiter::draw(glm::mat4x4 MVPMatrix, View *view, GLuint program, GLuint asd)
{
  ERR
      glEnable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  for (int i = 0; i < sourcesCount; i++)
  {
				Src *source = srcs[i];

    glm::vec3 dir = view->centers - view->eyes;
    glm::mat4x3 offests = glm::mat4x3();
    dir = glm::cross(dir, glm::vec3(0.0, 1.0, 0.0));
    dir = glm::normalize(dir);
    GLfloat wys = 1.f * source->particleSize;
    offests[0] = glm::vec3(dir.x * source->particleSize, -wys, dir.z * source->particleSize);
    offests[1] = glm::vec3(dir.x * source->particleSize, wys, dir.z * source->particleSize);
    offests[3] = glm::vec3(-dir.x * source->particleSize, wys, -dir.z * source->particleSize);
    offests[2] = glm::vec3(-dir.x * source->particleSize, -wys, -dir.z * source->particleSize);
    glm::vec3 kolorDymu = source->smokeColor;
    ERR
	glUniform3f(glGetUniformLocation(program, "kolorDymu"), kolorDymu.x, kolorDymu.y, kolorDymu.z);
    ERR
	glUniformMatrix4x3fv(glGetUniformLocation(program, "offsets"), 1, GL_FALSE, glm::value_ptr(offests));
    glUniform1f(glGetUniformLocation(program, "alpha"), source->alpha);
    glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(MVPMatrix));
    glUniform1f(glGetUniformLocation(program, "pointSize"), source->particleSize);
    ERR
	glDrawArrays(GL_POINTS, source->start, source->end - source->start);
    //	glDrawArrays(GL_POINTS,1000, 999);
  }
  glUseProgram(0);
  ERR
      glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
  ERR
}