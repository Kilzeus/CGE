#include "VertexElement.h"

using namespace Renderer;
VertexElement::VertexElement(
	const std::string& semantic,
	VertexElementType type,
	UINT index,
	bool instanceData
)
:semantic(semantic),type(type),index(index),
instanceData(instanceData)
{
}


bool VertexElement::operator==(const VertexElement& element) const
{
	if(type==element.type && semantic==element.semantic) return true;
	else return false;
}


bool VertexElement::operator!=(const VertexElement& element) const
{
	if(type!=element.type || semantic!=element.semantic) return true;
	else return false;
}


const std::string& VertexElement::getSemantic() const
{
	return semantic;
}


VertexElementType VertexElement::getType() const
{
	return type;
}


UINT VertexElement::getIndex() const
{
	return index;
}


bool VertexElement::isInstanceData() const
{
	return instanceData;
}