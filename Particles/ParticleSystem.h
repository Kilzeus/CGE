#pragma once
#include"ParticleUnit.h"
#include"ParticleRenderer.h"
#include"Texture.h"
#include<glm\glm.hpp>
#include<map>

/**
	Particle system holds data
	and is responsible for updating
	the particles
**/
namespace Particle
{
	/*
		Holds general information for a type of particle system. Information is shared
		by the emitters.
	*/
	class System
	{
		friend class Emitter;
		float minSpeed;
		float maxSpeed;
		glm::vec2 randomizeDirection; //x=left-right, y=up-down
		float minLifetime;
		float maxLifetime;
		glm::vec4 color;
		glm::vec3 size;
		bool infinite;
		float emitInterval;
		UINT particlesPerEmit; // how many particles to emit at once
		UINT maxParticles;	// how many particles are allowed to a single emitter
	public:
		System(const glm::vec4& color, UINT particlesPerEmit = 10, UINT maxParticles = 500,
			float emitInterval = 1.f, bool infinite = false);
		void setSpeed(float min, float max);
		void setLifetime(float min, float max);
		void setSize(const glm::vec3& size);
	};
}