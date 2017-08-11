#include"ParticleEmitterBox.h"


using namespace Particle;
ParticleEmitterBox::ParticleEmitterBox(const glm::vec3& position, const glm::vec3& boxWidths)
 : position(position), boxWidths(boxWidths), lastParticleEmit(0.0f,0.0f,0.0f)
{



}

const glm::vec3& ParticleEmitterBox::getNewPosition()
{

	this->lastParticleEmit.x = this->position.x + float( rand() % 100 ) * 0.02f * this->boxWidths.x - this->boxWidths.x;
	this->lastParticleEmit.y = this->position.y + float( rand() % 100 ) * 0.02f * this->boxWidths.y - this->boxWidths.y;
	this->lastParticleEmit.z = this->position.z + float( rand() % 100 ) * 0.02f * this->boxWidths.z - this->boxWidths.z;
	return this->lastParticleEmit;

}