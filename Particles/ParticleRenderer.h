#pragma once
#include"ParticleUnit.h"
#include"RenderContext.h"
namespace Particle
{
	class ParticleRenderer
	{
	public:
		virtual void renderParticles(Renderer::RenderContext* context, Unit* particles, UINT num) = 0;
	};
}