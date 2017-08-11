#pragma once
#include"ParticleEmitterShape.h"
#include<glm\glm.hpp>
namespace Particle
{
	class ParticleEmitterBox : public EmitterShape
	{
		glm::vec3 position;
		glm::vec3 lastParticleEmit;
		glm::vec3 boxWidths;

	public:

		ParticleEmitterBox(const glm::vec3& position, const glm::vec3& boxWidths);
		const glm::vec3& getNewPosition();

	};
}