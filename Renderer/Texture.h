#pragma once
#include"Types.h"
namespace Renderer
{
	enum TextureFormat{
		R8G8B8A8_unorm, R8G8B8A8_sint, R8G8B8A8_uint, B8G8R8A8_unorm,
		R32_float, R16G16_float, R32G32_float, R16G16B16A16_float,
		R16G16B16A16_unorm,
		R8_sint, R8_uint, R8_unorm
	};
	/**
		Represents a texture or an array of textures. 
	*/
	class Texture
	{
		friend class Device;
		bool renderTarget;
		TextureFormat format;
	protected:
		UINT arraySize;
		Uint2 dimensions;
		Texture(bool renderTarget, const Uint2& dimensions,TextureFormat format, UINT arraySize = 1);
	public:
		TextureFormat getFormat() const;
		const Uint2& getDimensions() const;
	};
}