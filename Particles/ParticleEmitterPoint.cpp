#include"ParticleEmitterPoint.h"


using namespace Particle;
ParticleEmitterPoint::ParticleEmitterPoint(const glm::vec3& position)
 : position( position )
{
}
 
const glm::vec3& ParticleEmitterPoint::getNewPosition()
{
	return this->position;
}