#include "Mesh.h"


using namespace AssetSystem;
Mesh::Mesh()
{
	type = Scene::ComponentType::Geometry;
}


Mesh::~Mesh()
{
}


void Mesh::onRender(Renderer::RenderContext* context)
{
	for each (MeshPart* part in meshParts)
	{
		part->onRender(context);
	}
}


void Mesh::onUpdate(double timeDelta)
{
	for each (MeshPart* part in meshParts)
	{
		part->onUpdate(timeDelta);
	}
}


MeshPart* Mesh::getPart(UINT index) const
{
	return meshParts[index];
}