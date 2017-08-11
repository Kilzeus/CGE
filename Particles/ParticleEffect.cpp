#include"ParticleEffect.h"

using namespace Particle;
EffectStage::EffectStage()
{
}

Effect::Effect()
 :dead(false),active(true),age(0.0f)
{
}

Scene::Node* Effect::getNode()
{
	return node;
}

bool Effect::isDead()
{
	return dead;
}

void Effect::setActive(bool value)
{

	active = value;

}

void Effect::update(float timestep)
{
	if(active)
	{
		age += timestep;
		if (!stages.empty())
		{
			std::map<float, EffectStage>::iterator iter = stages.begin();
			while (iter != stages.end())
			{
				if (iter->first >= age)
				{
					iter = stages.erase(iter);
				}
			}
		}
		else dead = true;
		if (!activeEmitters.empty())
		{
			std::list<Emitter*>::iterator iter = activeEmitters.begin();
			while (iter != activeEmitters.end())
			{
				if((*iter)->isDead())
				{
					delete *iter;
					iter = this->activeEmitters.erase(iter);
				}
				else
				{
					(*iter)->onUpdate(timestep);
					iter++;
				}
			}
			dead = false;
		}
	}
}

void Effect::addEffectStage(float time, const EffectStage& stage)
{
	stages.insert(std::make_pair(time, stage));
}
/*
void ParticleEffect::draw( ID3D11DeviceContext* devContext )
{

	std::list<ParticleEmitter*>::iterator iter = this->emitters.begin();
	while( iter != this->emitters.end())
	{
		(*iter)->draw( devContext );
		iter++;
	}

}*/