#pragma once
#include<glm\glm.hpp>
namespace GUI
{
	struct BoundingBox
	{
		glm::vec2 topLeft;
		glm::vec2 bottomRight;
		BoundingBox(
			const glm::vec2& topLeft,
			const glm::vec2& bottomRight
		):topLeft(topLeft),bottomRight(bottomRight) {};
	};
}