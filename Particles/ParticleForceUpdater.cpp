#include"ParticleForceUpdater.h"


using namespace Particle;
ParticleForceUpdater::ParticleForceUpdater()
{
}

void ParticleForceUpdater::updateParticle(Unit* particle, float time)
{

	particle->age += time;
	
	glm::vec3 dir = glm::normalize(particle->velocity); //from vel/sec to vel at frame
	float speed = glm::length(particle->velocity);
	
/*	glm::vec3 forces = force * time;
	if( forcePower > 0.0f )
	{
		glm::vec3 forceOriginDir = particle->position - forceOrigin;
		forceOriginDir = glm::normalize(forceOriginDir);
		forceOriginDir = forceOriginDir * this->forcePower * time;
		forces = forceOriginDir + forces ;
	}
	vel = vel + forces;*/

	particle->position += particle->velocity * time;
	//vel = glm::normalize(vel);
	//particle->velocity = vel;
}

void ParticleForceUpdater::applyForce( const glm::vec3& force )
{
	this->force + force;
}

void ParticleForceUpdater::setForceOrigin(const glm::vec3& position, float power)
{

	this->forceOrigin = position;
	this->forcePower = power;

}