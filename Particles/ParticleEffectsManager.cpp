#include"ParticleEffectsManager.h"

void ParticleEffectsManager::addParticleEffect( ParticleEffect* effect )
{

	this->effects.push_back( effect );

}

void ParticleEffectsManager::removeParticleEffect( ParticleEffect* effect )
{

	this->effects.remove( effect );
	
}

void ParticleEffectsManager::update( float time )
{
	if(!effects.empty())
	{
		std::list<ParticleEffect*>::iterator iter = this->effects.begin();
		while( iter != this->effects.end())
		{
			if(!(*iter)->isDead())
			{
				(*iter)->update( time );
				iter++;
			}
			else
			{
				delete *iter;
				iter = effects.erase( iter );
			}
		}
	}
}
/*
void ParticleEffectsManager::draw( ID3D11DeviceContext* devContext )
{

	std::list<ParticleEffect*>::iterator iter = this->effects.begin();
	while( iter != this->effects.end())
	{
		(*iter)->draw( devContext );
		iter++;
	}

}*/