#pragma once
#include"Collidable.h"
#include"windows.h"
#include<map>


namespace Physics
{
	class CollisionHandler
	{
	public:
		virtual bool handleCollision(Collidable* collidable1, Collidable* collidable2) = 0;
	};

	class CollisionManager
	{
		std::map<std::pair<UINT, UINT>, CollisionHandler*> collisionHandlers;
	public:
		void registerCollisionHandler(std::pair<UINT, UINT>& type, CollisionHandler* handler);
		void removeCollisionHandler(UINT type);
	};
}