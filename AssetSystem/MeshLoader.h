#pragma once
#include"Mesh.h"
#include"Device.h"
namespace AssetSystem
{
	class MeshLoader
	{
	public:
		MeshLoader();
		Mesh* loadMesh(Renderer::Device* device, std::string filename);
	};
}

