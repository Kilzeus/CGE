#include"ParticleEmitterSphere.h"


using namespace Particle;
ParticleEmitterSphere::ParticleEmitterSphere(const glm::vec3& position, float minRadius, float maxRadius)
 : position( position ), minRadius( minRadius ), maxRadius( maxRadius ), lastEmitPosition(0)
{

	

}

const glm::vec3& ParticleEmitterSphere::getNewPosition()
{
	glm::vec3 randomDir(float(rand() % 100) * 0.02f - 1.0f, float(rand() % 100) * 0.02f - 1.0f, float(rand() % 100) * 0.02f - 1.0f);
	randomDir = glm::normalize(randomDir);

	float length = float( rand() % 100 ) * 0.01f * ( this->maxRadius - this->minRadius ) + this->minRadius;
	randomDir *= length;
	lastEmitPosition = this->position + randomDir;
	return lastEmitPosition;
}