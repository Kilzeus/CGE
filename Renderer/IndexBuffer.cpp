#include "IndexBuffer.h"

using namespace Renderer;
IndexBuffer::IndexBuffer(IndexDataFormat format)
:format(format)
{
}


void IndexBuffer::setNumIndices(UINT numIndices)
{
	this->numIndices = numIndices;
}


const IndexDataFormat IndexBuffer::getIndexDataFormat() const
{
	return format;
}


UINT IndexBuffer::getNumIndices() const
{
	return numIndices;
}