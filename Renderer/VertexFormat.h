#pragma once
#include<vector>
#include"VertexElement.h"
#include"Definitions.h"
#include"Resource.h"
namespace Renderer
{
	class VertexFormat
	{
	protected:
		std::vector<VertexElement> elements;
	public:
		VertexFormat();
		~VertexFormat();
		void setElement(UINT index,const VertexElement& element);
		VertexElement getElement(UINT index);
		void addElement(const VertexElement& element);
		bool operator==(const VertexFormat& format) const;
		bool operator!=(const VertexFormat& format) const;
		virtual void finish(Resource* vertexShader)=0;
	};
}
