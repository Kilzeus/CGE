#include "VertexBuffer.h"

using namespace Renderer;
void VertexBuffer::setNumVertices(UINT numVertices)
{
	this->numVertices = numVertices;
}


const UINT VertexBuffer::getNumVertices() const
{
	return numVertices;
}


void VertexBuffer::setVertexByteSize(UINT size)
{
	vertexByteSize = size;
}


UINT VertexBuffer::getVertexByteSize() const
{
	return vertexByteSize;
}