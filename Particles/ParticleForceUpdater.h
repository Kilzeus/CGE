#pragma once
#include"ParticleUpdater.h"
namespace Particle
{
	/*
		Basic force based updater where you can add forces to
		achieve for example wind effects.
	*/
	class ParticleForceUpdater : public Updater
	{
		glm::vec3 force;
		glm::vec3 forceOrigin;
		float forcePower;
	public:
		ParticleForceUpdater();
		void updateParticle(Unit* particle, float time);
		void applyForce(const glm::vec3& force);
		void setForceOrigin(const glm::vec3& position, float power);
	};
}