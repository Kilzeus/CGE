#include"RenderOperation.h"

using namespace RenderFramework;
RenderOperation::RenderOperation(
	Renderer::VertexBuffer* vertexBuffer,
	Renderer::IndexBuffer* indexBuffer,
	Renderer::InstanceBuffer* instanceBuffer
):vertexBuffer(vertexBuffer),indexBuffer(indexBuffer),
instanceBuffer(instanceBuffer)
{
}


void RenderOperation::setMaterial(Material* material)
{
	this->material = material;
}


void RenderOperation::draw(Renderer::RenderContext* context)
{
	material->setMaterial(context);
	context->setVertexBuffer(vertexBuffer);
	for(int i=0;i<buffers.size();i++)
	{
		//i+1 because material properties at 0
		context->setGPUBuffer(i+1,buffers[i]);
	}
	if(indexBuffer) context->setIndexBuffer(indexBuffer);
	if(instanceBuffer) context->setInstanceBuffer(instanceBuffer);
	if(indexBuffer && instanceBuffer) context->drawIndexedInstanced();
	else if(indexBuffer && !instanceBuffer) context->drawIndexed();
	else if(!indexBuffer && instanceBuffer) context->drawInstanced();
	else context->draw();
}