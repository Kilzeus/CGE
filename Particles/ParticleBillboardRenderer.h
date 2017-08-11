#pragma once
#include"ParticleUnit.h"
#include"RenderContext.h"
#include"Device.h"
#include"Material.h"
#include"ParticleRenderer.h"
#include<glm\glm.hpp>
namespace Particle
{
	struct BillboardVertex
	{
		glm::vec3 position;
		float padding;
		glm::vec4 attributes1;
	};


	class ParticleBillboardRenderer : public ParticleRenderer
	{
		Renderer::VertexBuffer* vertexbuffer;
		RenderFramework::RenderEffect* effect;
		Renderer::Texture* texture;
		BillboardVertex* vertices;
		UINT maxParticles;
		const UINT vertsPerParticle = 6;
	public:
		ParticleBillboardRenderer(Renderer::Device* device, UINT maxParticles = 500);
		void renderParticles(Renderer::RenderContext* context, Unit* particles, UINT num);
		~ParticleBillboardRenderer();
	};
}

