#include"ParticleRingEmitter.h"


using namespace Particle;
ParticleRingEmitter::ParticleRingEmitter(const glm::vec3& planeNormal, float minRadius, float maxRadius)
 : minRadius( minRadius ), maxRadius( maxRadius ), normal( planeNormal ), lastEmitPosition(0.0f,0.0f,0.0f),
 position(glm::vec3(0.f, 0.f, 0.f))
{

	

}

const glm::vec3& ParticleRingEmitter::getNewPosition()
{

	glm::vec3 randomDir;
/*	glm::vec3 pos = XMLoadFloat3(&this->position);
	XMVECTOR normal = XMLoadFloat3( &this->normal );
	XMVECTOR result = XMPlaneFromPointNormal( pos, normal );
	
	randomDir.x = float( rand() % 100 ) * 0.02f - 1.0f;
	randomDir.y = 0.f;
	randomDir.z = float( rand() % 100 ) * 0.02f - 1.0f;
	XMVECTOR dir = XMLoadFloat3( &randomDir );
	dir = XMVector3Normalize( dir );
	XMStoreFloat3( &randomDir, dir );
	float length = float( rand() % 100 ) * 0.01f * ( this->maxRadius - this->minRadius ) + this->minRadius;
	randomDir.x *= length;
	randomDir.y *= length;
	randomDir.z *= length;
	this->lastEmitPosition.x = this->position.x + randomDir.x;
	this->lastEmitPosition.y = this->position.y + randomDir.y;
	this->lastEmitPosition.z = this->position.z + randomDir.z;
	return this->lastEmitPosition;*/
	glm::vec3 v;
	return v;
}