#include"CustomCollisionDispatcher.h"


using namespace Physics;
CustomCollisionDispatcher::CustomCollisionDispatcher(btCollisionConfiguration* collisionConfiguration)
: btCollisionDispatcher(collisionConfiguration)
{
}

bool CustomCollisionDispatcher::needsCollision(btCollisionObject* body0, btCollisionObject* body1)
{
	//((Collidable*)body0->getUserPointer())->onCollision();
	return btCollisionDispatcher::needsCollision( body0, body1 );
}


bool CustomCollisionDispatcher::needsResponse(btCollisionObject* body0, btCollisionObject* body1)
{
	return btCollisionDispatcher::needsResponse( body0, body1 );
}