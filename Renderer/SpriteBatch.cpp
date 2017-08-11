#include"SpriteBatch.h"

using namespace RenderFramework;
UINT SpriteBatch::bufferSize = 600;
SpriteBatch::SpriteBatch(
	Renderer::Device* device,
	RenderFramework::Material* material
):device(device),material(material)
{
	SpriteVertex* vertices = new SpriteVertex[bufferSize];
	batchingBuffers.push_back(vertices);
	bufferSizes.push_back(0);
	Renderer::VertexBuffer* buffer = 
		device->crateVertexBuffer(bufferSize*sizeof(SpriteVertex));
	vertexBuffers.push_back(buffer);
}

/**
	Call before rendering sprites.
*/
void SpriteBatch::begin()
{
	for(int i=0;i<bufferSizes.size();i++)
	{
		bufferSizes[i]=0;
	}
	buffersUsed = 0;
}

/**
	Issue a deferred draw order. The sprites will
	be drawn at once later.
*/
void SpriteBatch::draw(
	const glm::vec2& position,
	const glm::vec2& size,
	const glm::vec4& color,
	const glm::vec2& origin,
	const SpriteRect& rect,
	float colormod
)
{
	if(bufferSizes[buffersUsed] >= bufferSize)
		buffersUsed+=1;
	if(buffersUsed == batchingBuffers.size())
	{
		SpriteVertex* vertices = new SpriteVertex[bufferSize];
		batchingBuffers.push_back(vertices);
		bufferSizes.push_back(0);
		Renderer::VertexBuffer* buffer = 
		device->crateVertexBuffer(bufferSize*sizeof(SpriteVertex));
		vertexBuffers.push_back(buffer);
	}
	//bottomleft
	UINT index = bufferSizes[buffersUsed];
	batchingBuffers[buffersUsed][index].position.x = position.x;
	batchingBuffers[buffersUsed][index].position.y = position.y + size.y;
	batchingBuffers[buffersUsed][index].uv.x = rect.topLeft.x;
	batchingBuffers[buffersUsed][index].uv.y = rect.bottomRight.y;
	batchingBuffers[buffersUsed][index].color = color;
	batchingBuffers[buffersUsed][index].colormod = colormod;
	bufferSizes[buffersUsed]++;
	index++;

	//topleft
	batchingBuffers[buffersUsed][index].position.x = position.x;
	batchingBuffers[buffersUsed][index].position.y = position.y;
	batchingBuffers[buffersUsed][index].uv.x = rect.topLeft.x;
	batchingBuffers[buffersUsed][index].uv.y = rect.topLeft.y;
	batchingBuffers[buffersUsed][index].color = color;
	batchingBuffers[buffersUsed][index].colormod = colormod;
	bufferSizes[buffersUsed]++;
	index++;

	//bottomright
	batchingBuffers[buffersUsed][index].position.x = position.x + size.x;
	batchingBuffers[buffersUsed][index].position.y = position.y + size.y;
	batchingBuffers[buffersUsed][index].uv.x = rect.bottomRight.x;
	batchingBuffers[buffersUsed][index].uv.y = rect.bottomRight.y;
	batchingBuffers[buffersUsed][index].color = color;
	batchingBuffers[buffersUsed][index].colormod = colormod;
	bufferSizes[buffersUsed]++;
	index++;

	//bottomright
	batchingBuffers[buffersUsed][index].position.x = position.x + size.x;
	batchingBuffers[buffersUsed][index].position.y = position.y + size.y;
	batchingBuffers[buffersUsed][index].uv.x = rect.bottomRight.x;
	batchingBuffers[buffersUsed][index].uv.y = rect.bottomRight.y;
	batchingBuffers[buffersUsed][index].color = color;
	batchingBuffers[buffersUsed][index].colormod = colormod;
	bufferSizes[buffersUsed]++;
	index++;

	//topleft
	batchingBuffers[buffersUsed][index].position.x = position.x;
	batchingBuffers[buffersUsed][index].position.y = position.y;
	batchingBuffers[buffersUsed][index].uv.x = rect.topLeft.x;
	batchingBuffers[buffersUsed][index].uv.y = rect.topLeft.y;
	batchingBuffers[buffersUsed][index].color = color;
	batchingBuffers[buffersUsed][index].colormod = colormod;
	bufferSizes[buffersUsed]++;
	index++;

	//topright
	batchingBuffers[buffersUsed][index].position.x = position.x + size.x;
	batchingBuffers[buffersUsed][index].position.y = position.y;
	batchingBuffers[buffersUsed][index].uv.x = rect.bottomRight.x;
	batchingBuffers[buffersUsed][index].uv.y = rect.topLeft.y;
	batchingBuffers[buffersUsed][index].color = color;
	batchingBuffers[buffersUsed][index].colormod = colormod;
	bufferSizes[buffersUsed]++;
	index++;
}


void SpriteBatch::end(Renderer::RenderContext* context)
{
	for(int i=0;i<buffersUsed+1;i++)
	{
		vertexBuffers[i]->setData(
			&Resource(bufferSizes[i]*sizeof(SpriteVertex),batchingBuffers[i]),
			bufferSizes[i],
			sizeof(SpriteVertex)
		);
	}
	material->setMaterial(context);
	context->setPrimitiveTopology(Renderer::PrimitiveTopology::TriangleList);
	for(int i=0;i<buffersUsed+1;i++)
	{
		context->setVertexBuffer(vertexBuffers[i]);
		context->draw();
	}
}