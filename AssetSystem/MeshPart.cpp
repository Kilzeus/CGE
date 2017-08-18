#include "MeshPart.h"


using namespace AssetSystem;
MeshPart::MeshPart()
{
}


MeshPart::~MeshPart()
{
}


void MeshPart::onRender(Renderer::RenderContext* context)
{
	context->setPrimitiveTopology(Renderer::PrimitiveTopology::TriangleList);
	material->setMaterial(context);
	context->setVertexBuffer(vertexBuffer);
	context->draw();
}


void MeshPart::onUpdate(double timeDelta)
{

}


Renderer::VertexBuffer* MeshPart::getVertexbuffer()
{
	return vertexBuffer;
}