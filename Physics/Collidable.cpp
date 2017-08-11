#include"Collidable.h"


using namespace Physics;
MotionState::MotionState()
:collidable(0)
{
}

Collidable::Collidable(CollisionShape* collisionShape, float mass)
: motionState(new MotionState), collisionShape(collisionShape)
{
	motionState->attach(this);
	btRigidBody::btRigidBodyConstructionInfo info(mass, 
		motionState, collisionShape->shape, btVector3(1.0f, 1.0f, 1.0f));
	rigidBody = new btRigidBody(info);
	rigidBody->setUserPointer(this);
	rigidBody->setActivationState(DISABLE_DEACTIVATION);
}


void MotionState::attach(Collidable* collidable)
{
	this->collidable = collidable;
}


/*
	Gets initial location and rotation from the collidable. Also
	kinetic body calls this on update.
*/
void MotionState::getWorldTransform(btTransform& worldTrans) const
{
	if(!collidable) return;
	const glm::vec3& pos = collidable->getPosition();
	worldTrans.setOrigin( btVector3(pos.x, pos.y, pos.z));
	const glm::quat& rot = collidable->getRotation();
	worldTrans.setRotation( btQuaternion( rot.x, rot.y, rot.z, rot.w));
}


/*
Gets location and rotation from physics body and sets them on
the associated Collidable object
*/
void MotionState::setWorldTransform( const btTransform& worldTrans )
{

	if(!collidable ) return;
	btVector3 pos = worldTrans.getOrigin();
	collidable->setPosition(glm::vec3( pos.x(), pos.y(), pos.z()));
	btQuaternion rot = worldTrans.getRotation();
	collidable->setRotation(glm::quat(rot.x(), rot.y(), rot.z(), rot.getW()));
}


btRigidBody* Collidable::getRigidBody()
{
	return rigidBody;
}


const glm::vec3& Collidable::getPosition() const
{
	return position;
}


const glm::quat& Collidable::getRotation() const
{
	return rotation;
}


void Collidable::setPosition(const glm::vec3& position)
{
	this->position = position;
}


void Collidable::setRotation(const glm::quat& rotation)
{
	this->rotation = rotation;
}


void Collidable::onUpdate(double deltatime)
{
	
}


