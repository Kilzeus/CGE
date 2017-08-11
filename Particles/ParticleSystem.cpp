#include"ParticleSystem.h"


using namespace Particle;
System::System(const glm::vec4& color, UINT particlesPerEmit, UINT maxParticles,
	float emitInterval, bool infinite)
:particlesPerEmit(particlesPerEmit), emitInterval(emitInterval), 
maxParticles(maxParticles), infinite(infinite), color(color), 
size(glm::vec3(1)), randomizeDirection(glm::vec2(1))
{
	minSpeed = 0.2f;
	maxSpeed = 0.4f;
	minLifetime = 0.9f;
	maxLifetime = 1.1f;
}


void System::setSpeed(float min, float max)
{
	minSpeed = min;
	maxSpeed = max;
}


void System::setLifetime(float min, float max)
{
	minLifetime = min;
	maxLifetime = max;
}


void System::setSize(const glm::vec3& size)
{
	this->size = size;
}