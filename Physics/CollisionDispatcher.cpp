#include"CollisionDispatcher.h"


using namespace Physics;
void CollisionDispatcher::registerCollisionHandler( UINT priority, CollisionHandler handler )
{
	//std::map<UINT,CollisionHandler> collisionHandlers
	collisionHandlers.insert( std::make_pair( priority, handler ));
}


void CollisionDispatcher::removeCollisionHandler( CollisionHandler handler )
{
	std::multimap<UINT,CollisionHandler>::iterator iter = this->collisionHandlers.begin();
	while( iter != this->collisionHandlers.end())
	{
		if( iter->second == handler )
		{
			iter = this->collisionHandlers.erase( iter );
			return;
		}
		iter++;
	}
}