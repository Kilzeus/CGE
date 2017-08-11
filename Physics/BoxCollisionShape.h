#pragma once
#include"CollisionShape.h"
#include<glm\glm.hpp>
namespace Physics
{
	class BoxCollisionShape : public CollisionShape
	{
	public:
		BoxCollisionShape(const glm::vec3& halfExtends);
		~BoxCollisionShape();
	};
}
