#pragma once
#include<glm\glm.hpp>

namespace Particle
{
	class EmitterShape
	{
	public:
		virtual const glm::vec3& getNewPosition() = 0;
	};
}