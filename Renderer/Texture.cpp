#include"Texture.h"

using namespace Renderer;
Texture::Texture(bool renderTarget, const Uint2& dimensions, 
	TextureFormat format, UINT arraySize) //, ID3D11ShaderResourceView* texture )
	:renderTarget(renderTarget), format(format), 
	arraySize(arraySize), dimensions(dimensions)
{
}


TextureFormat Texture::getFormat() const
{
	return format;
}


const Uint2& Texture::getDimensions() const
{
	return dimensions;
}