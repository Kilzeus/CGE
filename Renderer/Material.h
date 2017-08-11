#pragma once
#include"Texture.h"
#include"MaterialProperty.h"
#include"VertexShader.h"
#include"FragmentShader.h"
#include"GeometryShader.h"
#include"VertexFormat.h"
#include"GPUBuffer.h"
#include"RenderContext.h"
#include"EffectGroup.h"
#include<vector>
/**
	Interface class for material. Independent
	of the rendering api.
*/
namespace RenderFramework
{
	class Material
	{	
		friend class RenderOperation;
		std::vector<Renderer::Texture*> textures;
		Renderer::VertexShader* vertexShader;
		Renderer::FragmentShader* fragmentShader;
		Renderer::GeometryShader* geometryShader;
		MaterialProperty* materialProperties;
		//RenderEffect* effect;

	public:
		Material();
		void setTexture(UINT index,Renderer::Texture* texture);
		Renderer::Texture* getTexture(UINT index);
		void setRenderEffect(RenderEffect* effect);
		void setMaterialProperties(MaterialProperty* materialProperties);
		void setMaterial(Renderer::RenderContext* context);
		virtual UINT getNumTextures() const;
	};
}