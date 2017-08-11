#include"Engine.h"


using namespace Physics;
Engine::Engine(const glm::vec3& gravity, int maxSteps)
{
	collisionConfiguration = new btDefaultCollisionConfiguration;
	dispatcher = new CustomCollisionDispatcher( this->collisionConfiguration );
	btBroadphaseInterface = new btDbvtBroadphase;
	constraintSolver = new btSequentialImpulseConstraintSolver;
	physicsWorld = new btDiscreteDynamicsWorld( this->dispatcher, this->btBroadphaseInterface, this->constraintSolver, this->collisionConfiguration );
	physicsWorld->setGravity( btVector3( gravity.x, gravity.y, gravity.z ));
	physicsWorld->setInternalTickCallback(Engine::btInternalTickCallback, 0, true);
	maxSubsteps = maxSteps;
}

void Engine::btInternalTickCallback(btDynamicsWorld *world, btScalar timeStep)
{

      btCollisionObjectArray objects = world->getCollisionObjectArray();
     // world->clearForces();
      for( int i = 0; i < objects.size(); i++ )
      {
			Collidable* collidable = static_cast<Collidable*>(objects[i]->getUserPointer());
			collidable->onFixedUpdate(timeStep);
      }
}

void Engine::update(float timestep)
{
	if (timestep > 0.f)
		physicsWorld->stepSimulation(timestep, maxSubsteps);
}

void Engine::addComponents(Collidable* collidable)
{
	physicsWorld->addRigidBody(collidable->getRigidBody());
}