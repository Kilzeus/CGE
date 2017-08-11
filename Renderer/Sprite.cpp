#include"Sprite.h"
#include"Device.h"

using namespace RenderFramework;
Sprite::Sprite(
	Renderer::Device* device,
	const glm::vec2& position,
	const glm::vec2& size,
	const glm::vec4& color,
	Material* material,
	float colormod
	) :position(position), size(size), material(material)
{
	UINT numVerts = 6;
	vbuffer = device->crateVertexBuffer(numVerts*sizeof(SpriteVertex));
	SpriteVertex* vertices = new SpriteVertex[6];
	UINT index = 0;
	//bottomleft
	vertices[index].position.x = position.x;
	vertices[index].position.y = position.y + size.y;
	vertices[index].uv = glm::vec2(0.f,1.f);
	vertices[index].color = color;
	vertices[index].colormod = colormod;
	index++;

	//topleft
	vertices[index].position.x = position.x;
	vertices[index].position.y = position.y;
	vertices[index].uv = glm::vec2(0.f, 0.f);
	vertices[index].color = color;
	vertices[index].colormod = colormod;
	index++;

	//bottomright
	vertices[index].position.x = position.x + size.x;
	vertices[index].position.y = position.y + size.y;
	vertices[index].uv = glm::vec2(1.f, 1.f);
	vertices[index].color = color;
	vertices[index].colormod = colormod;
	index++;

	//bottomright
	vertices[index].position.x = position.x + size.x;
	vertices[index].position.y = position.y + size.y;
	vertices[index].uv = glm::vec2(1.f, 1.f);
	vertices[index].color = color;
	vertices[index].colormod = colormod;
	index++;

	//topleft
	vertices[index].position.x = position.x;
	vertices[index].position.y = position.y;
	vertices[index].uv = glm::vec2(0.f, 0.f);
	vertices[index].color = color;
	vertices[index].colormod = colormod;
	index++;

	//topright
	vertices[index].position.x = position.x+size.x;
	vertices[index].position.y = position.y;
	vertices[index].uv = glm::vec2(1.f, 0.f);
	vertices[index].color = color;
	vertices[index].colormod = colormod;
	index++;

	vbuffer->setData(&Resource(numVerts*sizeof(SpriteVertex), vertices), numVerts, sizeof(SpriteVertex));

}


void Sprite::render(Renderer::RenderContext* context)
{
	material->setMaterial(context);
	context->setPrimitiveTopology(Renderer::PrimitiveTopology::TriangleList);
	context->setVertexBuffer(vbuffer);
	context->draw();
}


void Sprite::setMaterial(Material* material)
{
	this->material = material;
}