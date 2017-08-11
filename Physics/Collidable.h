#pragma once
#include"CollisionShape.h"
#include"RenderContext.h"
#include<glm\glm.hpp>
#include<glm\ext.hpp>
#include<btBulletCollisionCommon.h>

namespace Physics
{
	class MotionState : public btMotionState
	{
		friend class Collidable;
		Collidable* collidable;
		MotionState();
	public:
		void attach(Collidable* collidable);
		void getWorldTransform(btTransform& worldTrans) const;
		void setWorldTransform(const btTransform& worldTrans);
	};

	/*
		This component updates Scene::Node transform when attached to it.
		Node held by this object is meant to be attached to Scene root.
	*/
	class Collidable
	{
		int id;
		MotionState* motionState;
		CollisionShape* collisionShape;
		btRigidBody* rigidBody;
		glm::vec3 position;
		glm::quat rotation;
	public:
		Collidable(CollisionShape* collisionShape, float mass=1.f);
		void onFixedUpdate(float timestep) {};
		btRigidBody* getRigidBody();
		const glm::vec3& getPosition() const;
		const glm::quat& getRotation() const;
		void setPosition(const glm::vec3& position);
		void setRotation(const glm::quat& rotation);
		void onUpdate(double deltatime);
	};
}