#include"CollisionManager.h"


using namespace Physics;
void CollisionManager::registerCollisionHandler( std::pair<UINT,UINT>& type, CollisionHandler* handler )
{
	collisionHandlers.insert(std::make_pair(type, handler));
}