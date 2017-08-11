#pragma once
#include"Definitions.h"
#include"GPUBuffer.h"
#include<vector>
namespace RenderFramework
{
	union MaterialConstant
	{
		struct Int4{
			int x;
			int y;
			int z;
			int w;
		}int4;
		struct Float4
		{
			float x;
			float y;
			float z;
			float w;
		}float4;
	};

	/**
		Container for material constants
	*/
	class MaterialProperty
	{
		friend class Material;
		MaterialConstant* constants;
		bool changed;
		UINT numConstants;
		Renderer::GPUBuffer* buffer;

		void generateGPUBuffer();
	public:
		MaterialProperty(Renderer::GPUBuffer* buffer,UINT numConstants = 3);
		~MaterialProperty();
		void setConstant(UINT index,const MaterialConstant& constant);
	};
}