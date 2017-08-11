#pragma once
#include"btBulletDynamicsCommon.h"

namespace Physics
{
	class CustomCollisionDispatcher : public btCollisionDispatcher
	{
	public:
		CustomCollisionDispatcher(btCollisionConfiguration* collisionConfiguration);
		bool needsCollision(btCollisionObject* body0, btCollisionObject* body1);
		bool needsResponse(btCollisionObject* body0, btCollisionObject* body1);
	};
}