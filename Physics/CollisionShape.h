#pragma once
#include"btBulletDynamicsCommon.h"

namespace Physics
{
	class CollisionShape
	{
		friend class Collidable;
	protected:
		btCollisionShape* shape;
	};
}

