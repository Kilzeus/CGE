#include"ParticleEmitter.h"


using namespace Particle;
Emitter::Emitter(System& system, ParticleRenderer* renderer, EmitterShape* emitterShape, 
	Updater* updater)
 : system(system), lifetime(lifetime), emitterShape(emitterShape),
 active(true), updater(updater), numParticles(0U), age(0.f), timer(0.f),
 renderer(renderer)
{
	infinite = system.infinite;
	particles = new Unit[system.maxParticles];
	type = Scene::ComponentType::Other;
}

Emitter::~Emitter()
{
	delete[] particles;
	delete updater;
}

bool Emitter::isActive()
{
	return active;
}

void Emitter::setActive(bool isActive)
{
	active = isActive;
}

bool Emitter::isDead()
{
	if (lifetime <= 0.f) return true;
	else return false;
}

void Emitter::emit(UINT num)
{

	timer = 0.f;
	for (int i = 0; i < num && numParticles < system.maxParticles; i++)
	{
		Unit* particle = &particles[numParticles];
		glm::vec3 vel;
		float randomX = system.randomizeDirection.x;
		float randomY = system.randomizeDirection.y;
		vel.x += sin((float)( rand() % 100 ) * 0.02f * randomX - randomX );
		vel.z += sin((float)( rand() % 100 ) * 0.02f * randomX - randomX );
		vel.y += sin((float)( rand() % 100 ) * 0.02f * randomY - randomY );

		float minSpeed = system.minSpeed;
		float maxSpeed = system.maxSpeed;
		vel.x *= minSpeed + (float)( rand() % 100 ) * 0.01f * ( maxSpeed - minSpeed );
		vel.y *= minSpeed + (float)( rand() % 100 ) * 0.01f * ( maxSpeed - minSpeed );
		vel.z *= minSpeed + (float)( rand() % 100 ) * 0.01f * ( maxSpeed - minSpeed );
			
		particle->velocity = vel;
		particle->age = 0.0f;
		particle->position = this->emitterShape->getNewPosition();
		particle->lifetime = system.minLifetime + (float)(rand() % 100) * 0.01f * (system.maxLifetime - system.minLifetime);
		particle->size = system.size;
		numParticles++;
	}
}

void Emitter::onUpdate(double deltatime)
{
	age += deltatime;
	timer += deltatime;
	if (timer >= system.emitInterval)
	{
		emit(system.particlesPerEmit);
		timer = 0.f;
	}
	for (int i = 0; i < system.maxParticles && numParticles > 0; i++)
	{
		if (particles[i].age < particles[i].lifetime)
		{
			updater->updateParticle(&particles[i], deltatime);
		}
		else if (particles[i].age > 0.f)
		{
			numParticles--;
			Unit last = particles[numParticles];
			particles[i].age = 0;
			particles[numParticles] = last;
			particles[i] = last;
		}
	}
}

void Emitter::onRender(Renderer::RenderContext* context)
{
	renderer->renderParticles(context, particles, numParticles);
}