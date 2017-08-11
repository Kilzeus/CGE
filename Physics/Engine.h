#pragma once
#include"btBulletDynamicsCommon.h"
#include"CustomCollisionDispatcher.h"
#include"Collidable.h"
#include<glm\glm.hpp>

/*
class cCustomFilterCallback : public btOverlapFilterCallback
{

	public:
	
	virtual bool needBroadphaseCollision( btBroadphaseProxy* proxy0,btBroadphaseProxy* proxy1 )const;
	
};*/
namespace Physics
{
	class Engine
	{
		btConstraintSolver* constraintSolver;
		btDispatcher* dispatcher;
		btCollisionConfiguration* collisionConfiguration;
		btBroadphaseInterface* btBroadphaseInterface;
		btDynamicsWorld* physicsWorld;
		int maxSubsteps;

		static void btInternalTickCallback(btDynamicsWorld *world, btScalar timeStep);
	public:
		Engine(const glm::vec3& gravity = glm::vec3(0.0f, -9.8f, 0.0f), int maxSteps = 10);
		void update(float timestep);
		void addComponents(Collidable* collidable);
	};
}