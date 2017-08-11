#pragma once
#include"ParticleEmitterShape.h"
namespace Particle
{
	class ParticleEmitterSphere : public EmitterShape
	{
		glm::vec3 position;
		float minRadius;
		float maxRadius;
		glm::vec3 lastEmitPosition;
	public:
		ParticleEmitterSphere(const glm::vec3& position, float minRadius, float maxRadius);
		const glm::vec3& getNewPosition();
	};
}