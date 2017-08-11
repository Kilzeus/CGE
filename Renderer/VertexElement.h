#pragma once
#include<string>
#include"Definitions.h"
namespace Renderer
{
	enum VertexElementType{ 
		FLOAT1, FLOAT2, FLOAT3, FLOAT4, Int1, Int2, Int3, Int4,
		UInt1, UInt2, UInt3, UInt4
	};
	class VertexElement
	{
		friend class VertexFormat;
		VertexElementType type;
		std::string semantic;
		UINT index;
		bool instanceData;
	public:
		VertexElement(
			const std::string& semantic,
			VertexElementType type,
			UINT index = 0,
			bool instanceData = false
		);
		const std::string& getSemantic() const;
		VertexElementType getType() const;
		UINT getIndex() const;
		bool isInstanceData() const;
		bool operator==(const VertexElement& element) const;
		bool operator!=(const VertexElement& element) const;
	};
}
