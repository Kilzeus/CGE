#pragma once
#include"Component.h"
#include"ParticleUnit.h"
#include"ParticleSystem.h"
#include"ParticleEmitterShape.h"
#include"ParticleUpdater.h"
#include"ParticleRenderer.h"
#include<glm\glm.hpp>
#include<queue>
namespace Particle
{
	/*
		Emits particles.
	*/
	class Emitter : public Scene::Component
	{
		Unit* particles;
		UINT numParticles;
		System& system;
		EmitterShape* emitterShape;
		Updater* updater;
		ParticleRenderer* renderer;
		float lifetime;
		float age;
		float timer;
		bool infinite;
		bool active;
	public:
		Emitter(System& system, ParticleRenderer* renderer, EmitterShape* emitterShape,
			Updater* updater);
		~Emitter();
		void onUpdate(double deltatime);
		void onRender(Renderer::RenderContext* context);
		void setActive(bool active);
		bool isActive();
		bool isDead();
		void emit(UINT numParticles); // fire emitter manually
	};
}