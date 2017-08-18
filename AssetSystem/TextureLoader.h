#pragma once
#ifndef FREEIMAGE_LIB
#define  FREEIMAGE_LIB
#endif
#include"FreeImage.h"
#include"Texture.h"
#include"Device.h"
#include<string>
namespace AssetSystem
{
	/**
		Loads textures from files.
	*/
	class TextureLoader
	{
		Renderer::Device* device;
		static UINT instances;
	public:
		TextureLoader(Renderer::Device* device);
		~TextureLoader();
		Renderer::Texture* loadTexture(const std::string name);
	};
}