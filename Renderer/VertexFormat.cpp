#include "VertexFormat.h"

using namespace Renderer;
VertexFormat::VertexFormat(void)
{
}


VertexFormat::~VertexFormat(void)
{
}

void VertexFormat::setElement(UINT index,const VertexElement& element)
{
	elements[index]=element;
}


void VertexFormat::addElement(const VertexElement& element)
{
	elements.push_back(element);
}


bool VertexFormat::operator==(const VertexFormat& format) const
{
	if(elements.size()!=format.elements.size()) return false;
	for(int i=0;i<elements.size();i++)
	{
		if(elements[i]!=format.elements[i]) return false;
	}
	return true;
}


bool VertexFormat::operator!=(const VertexFormat& format) const
{
	return !(*this==format);
}