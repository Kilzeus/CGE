#pragma once
#include"Component.h"
#include"MeshPart.h"
#include<vector>
#include<glm\glm.hpp>
namespace AssetSystem
{
	/*
		Container for MeshParts, one for each material.
	*/
	class Mesh : public Scene::Component
	{
		friend class MeshLoader;
		std::vector<MeshPart*> meshParts;
	public:
		Mesh();
		~Mesh();
		void onRender(Renderer::RenderContext* context);
		void onUpdate(double timeDelta);
		MeshPart* getPart(UINT index) const;
	};
}

