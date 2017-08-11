#pragma once
#include<glm\glm.hpp>
#include<glm\ext.hpp>
namespace Scene
{
	struct PositionComponent
	{
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 size;
	};
}

