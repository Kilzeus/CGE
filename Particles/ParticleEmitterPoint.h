#pragma once
#include"ParticleEmitterShape.h"
namespace Particle
{
	class ParticleEmitterPoint : public EmitterShape
	{
		glm::vec3 position;
	public:
		ParticleEmitterPoint(const glm::vec3& position);
		const glm::vec3& getNewPosition();
	};
}
