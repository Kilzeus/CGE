#include "ParticleBillboardRenderer.h"
#include"EffectLoader.h"
#include"TextureLoader.h"


using namespace Particle;
ParticleBillboardRenderer::ParticleBillboardRenderer(
	Renderer::Device* device, UINT maxParticles)
{
	vertexbuffer = device->crateVertexBuffer(sizeof(BillboardVertex)*
		vertsPerParticle * maxParticles, false);
	RenderFramework::EffectLoader loader;
	RenderFramework::EffectGroup* effectGroup = loader.loadEffect(device, "particleEffects.fx");
	effect = effectGroup->getEffect("basic");
	vertices = new BillboardVertex[maxParticles];
	this->maxParticles = maxParticles;
	AssetSystem::TextureLoader textureLoader(device);
	texture = textureLoader.loadTexture("explosion_1.png");
}


ParticleBillboardRenderer::~ParticleBillboardRenderer()
{
}


void ParticleBillboardRenderer::renderParticles(Renderer::RenderContext* context, Unit* particles, UINT num)
{
	for (UINT i = 0; i < num; i++)
	{
		UINT index = 0;
		vertices[i * vertsPerParticle + index].position = particles[i].position;
		vertices[i * vertsPerParticle + index].position.z -= particles[i].size.x;
		vertices[i * vertsPerParticle + index].position.y += particles[i].size.y;
		vertices[i * vertsPerParticle + index].attributes1.x = 0;
		vertices[i * vertsPerParticle + index].attributes1.y = 0;
		vertices[i * vertsPerParticle + index].attributes1.z = particles[i].size.x;
		vertices[i * vertsPerParticle + index].attributes1.w = particles[i].age / particles[i].lifetime;
		index++;
		vertices[i * vertsPerParticle + index].position = particles[i].position;
		vertices[i * vertsPerParticle + index].position.z += particles[i].size.x;
		vertices[i * vertsPerParticle + index].position.y += particles[i].size.y;
		vertices[i * vertsPerParticle + index].attributes1.x = 1;
		vertices[i * vertsPerParticle + index].attributes1.y = 0;
		vertices[i * vertsPerParticle + index].attributes1.z = particles[i].size.x;
		vertices[i * vertsPerParticle + index].attributes1.w = particles[i].age / particles[i].lifetime;
		index++;
		vertices[i * vertsPerParticle + index].position = particles[i].position;
		vertices[i * vertsPerParticle + index].position.z -= particles[i].size.x;
		vertices[i * vertsPerParticle + index].position.y -= particles[i].size.y;
		vertices[i * vertsPerParticle + index].attributes1.x = 0;
		vertices[i * vertsPerParticle + index].attributes1.y = 1;
		vertices[i * vertsPerParticle + index].attributes1.z = particles[i].size.x;
		vertices[i * vertsPerParticle + index].attributes1.w = particles[i].age / particles[i].lifetime;
		index++;
		vertices[i * vertsPerParticle + index].position = particles[i].position;
		vertices[i * vertsPerParticle + index].position.z -= particles[i].size.x;
		vertices[i * vertsPerParticle + index].position.y -= particles[i].size.y;
		vertices[i * vertsPerParticle + index].attributes1.x = 0;
		vertices[i * vertsPerParticle + index].attributes1.y = 1;
		vertices[i * vertsPerParticle + index].attributes1.z = particles[i].size.x;
		vertices[i * vertsPerParticle + index].attributes1.w = particles[i].age / particles[i].lifetime;
		index++;
		vertices[i * vertsPerParticle + index].position = particles[i].position;
		vertices[i * vertsPerParticle + index].position.z += particles[i].size.x;
		vertices[i * vertsPerParticle + index].position.y += particles[i].size.y;
		vertices[i * vertsPerParticle + index].attributes1.x = 1;
		vertices[i * vertsPerParticle + index].attributes1.y = 0;
		vertices[i * vertsPerParticle + index].attributes1.z = particles[i].size.x;
		vertices[i * vertsPerParticle + index].attributes1.w = particles[i].age / particles[i].lifetime;
		index++;
		vertices[i * vertsPerParticle + index].position = particles[i].position;
		vertices[i * vertsPerParticle + index].position.z += particles[i].size.x;
		vertices[i * vertsPerParticle + index].position.y -= particles[i].size.y;
		vertices[i * vertsPerParticle + index].attributes1.x = 1;
		vertices[i * vertsPerParticle + index].attributes1.y = 1;
		vertices[i * vertsPerParticle + index].attributes1.z = particles[i].size.x;
		vertices[i * vertsPerParticle + index].attributes1.w = particles[i].age / particles[i].lifetime;
		index++;
	}
	vertexbuffer->setData(&Resource(sizeof(BillboardVertex) * vertsPerParticle * num, sizeof(BillboardVertex), vertices), num * vertsPerParticle, sizeof(BillboardVertex));

	//set state and draw
	context->setVertexFormat(effect->getVertexShader()->getVertexFormat());
	context->setVertexShader(effect->getVertexShader());
	context->setFragmentShader(effect->getFragmentShader());
	context->setVertexBuffer(vertexbuffer);
	context->setPrimitiveTopology(Renderer::PrimitiveTopology::TriangleList);
	context->setTexture(3, texture);
	context->draw();
}
