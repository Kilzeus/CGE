#pragma once
#include"Font.h"
#include"Device.h"
#include <ft2build.h> 
#include FT_FREETYPE_H
namespace GUI
{
	class FontLoader
	{
		FT_Library freeType;

		void insertCharToTexture(char* texture,FT_Bitmap bitmap);
	public:
		FontLoader();
		Font* loadFont(Renderer::Device* device, const std::string file, UINT size, bool antiAliasing = true, bool debug = false);
	};
}