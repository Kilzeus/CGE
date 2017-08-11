#pragma once
#include"Collidable.h"
#include"windows.h"
#include<map>


namespace Physics
{
	typedef bool(*CollisionHandler)(Collidable*, Collidable*);

	class CollisionDispatcher
	{
		std::multimap<UINT, CollisionHandler> collisionHandlers;
	public:
		void registerCollisionHandler(UINT priority, CollisionHandler handler);
		void removeCollisionHandler(CollisionHandler handler);
	};
}