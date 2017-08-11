#pragma once
#include"ParticleUnit.h"
namespace Particle
{
	/*
		Interface for particle updater. Responsible for updating particle attributes.
	*/
	class Updater
	{
	public:
		virtual void updateParticle(Unit* particle, float time) = 0;
	};
}