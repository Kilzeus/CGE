#pragma once
#include<glm\glm.hpp>

/*
	Represents one particle.
*/
namespace Particle
{
	struct Unit
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 velocity;
		float lifetime;
		float age;
		glm::vec3 size;
	};
}