#pragma once
#include"ParticleEmitterShape.h"
namespace Particle
{
	class ParticleRingEmitter : public EmitterShape
	{
		glm::vec3 lastEmitPosition;
		glm::vec3 position;
		glm::vec3 normal;
		float minRadius;
		float maxRadius;
	public:

		ParticleRingEmitter(const glm::vec3& planeNormal, float minRadius, float maxRadius);
		const glm::vec3& getNewPosition();

	};
}