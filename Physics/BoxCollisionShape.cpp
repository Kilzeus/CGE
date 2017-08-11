#include "BoxCollisionShape.h"


using namespace Physics;
BoxCollisionShape::BoxCollisionShape(const glm::vec3& halfExtends)
{
	shape = new btBoxShape(btVector3(halfExtends.x, halfExtends.y, halfExtends.z));
}


BoxCollisionShape::~BoxCollisionShape()
{
	delete shape;
}
