#pragma once
#include"ParticleEmitter.h"
#include"Node.h"
#include<map>
#include<list>

namespace Particle
{
	/*
		Signifies a stage when an emitter spawns. 
		Effect consists of one to N of these.
	*/
	struct EffectStage
	{
		EffectStage();
		Emitter* emitter;
		float lifetime;

	};

	/*
		An effect consists of one to N stages that are started at
		specified times.
	*/
	class Effect
	{
		std::map<float,EffectStage> stages;
		std::list<Emitter*> activeEmitters;
		bool dead;
		bool active;
		float age;
		Scene::Node* node;
	public:
		Effect();
		void addEffectStage(float time, const EffectStage& stage);
		Scene::Node* getNode();
		void setActive(bool value);
		void update(float timestep);
		bool isDead();
	};
}