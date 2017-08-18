#include"FontLoader.h"
#define NOMINMAX
#include<Windows.h>
#include<algorithm>

using namespace GUI;
FontLoader::FontLoader()
{
	UINT error = FT_Init_FreeType(&freeType);
}


void FontLoader::insertCharToTexture(char* texture,FT_Bitmap bitmap)
{

}


Font* FontLoader::loadFont(Renderer::Device* device, const std::string file,UINT size,bool antiAliasing, bool debug)
{
	Font* font = 0;
	FT_Face face = 0;

	UINT error = FT_New_Face(freeType,file.c_str(),0,&face);
	if (error == FT_Err_Unknown_File_Format)
	{
		return 0;
	}
	if (error = FT_Set_Pixel_Sizes(face, size, size))
		return 0;
	std::vector<CharacterInfo> characterInfos(128);
	UINT baseCharOffset = 32;
	std::map<std::pair<char, char>, float> kerning;
	//find max width and height of characters, also total width
	int maxWidth = 0, maxHeight = 0;
	for (char c = baseCharOffset; c<127; c++)
	{
		error = FT_Load_Char(face, c, FT_LOAD_RENDER);
		if (error)
		{
			continue;
		}
		if (!face->glyph->bitmap.buffer)
			continue;
		int btmWidth = face->glyph->bitmap.width * (float(face->glyph->metrics.horiAdvance) / float(face->glyph->metrics.width));
		int btmHeight = face->glyph->bitmap.rows + face->glyph->bitmap.rows  * (float((face->glyph->metrics.horiBearingY)) / float(face->glyph->metrics.height));
		maxWidth = std::max(maxWidth, btmWidth);
		maxHeight = std::max(maxHeight, btmHeight);
		for (char k = baseCharOffset; k < 127; k++)
		{
			FT_Vector akern;
			FT_Get_Kerning(face, c, k, FT_KERNING_UNSCALED, &akern);
			float kern = float(akern.x) / float(face->glyph->metrics.width);
			kerning.insert(std::pair<std::pair<char, char>, float>(std::pair<char, char>(c, k), kern));
		}
	}
	UINT total = 2;
	while (total < maxWidth * maxHeight * (127-32))
	{
		total *= 2;
	}
	Renderer::Uint2 dm;
	dm.x = sqrt(total);
	dm.y = dm.x;
	unsigned char* data = new unsigned char[total];
	ZeroMemory(data, sizeof(char)*total);
	int ptrWidth = 0, ptrHeight = 0;
	for (char c = baseCharOffset; c < 127; c++)
	{
		bool error = false;
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			error = true;
		if (!face->glyph->bitmap.buffer)
			error = true;

		if (!error)
		{
			FT_Pos advance = face->glyph->metrics.horiAdvance;
			FT_Pos bearingX = face->glyph->metrics.horiBearingX;
			if (face->glyph->metrics.width != 0) characterInfos[c].bearings.x = float(bearingX) / float(face->glyph->metrics.width);
			FT_Pos bearingY = face->glyph->metrics.horiBearingY;
			if (face->glyph->metrics.height != 0) characterInfos[c].bearings.y = (float(bearingY)) / float(face->glyph->metrics.height);
			UINT rows = face->glyph->bitmap.rows;
			characterInfos[c].advance = float(advance) / float(face->glyph->metrics.width); // relative advance
			characterInfos[c].bitmapDimensions.x = face->glyph->bitmap.pitch;
			characterInfos[c].bitmapDimensions.y = face->glyph->bitmap.rows;
			UINT ptr = characterInfos[c].bearings.y * characterInfos[c].bitmapDimensions.y;
			for (int i = 0; i < rows; i++)
			{
				UINT width = face->glyph->bitmap.pitch;
				for (int p = 0; p < width; p++)
				{
					unsigned char px = face->glyph->bitmap.buffer[i*width + p];
					data[(ptrHeight + i) * dm.x + ptrWidth + p] = px;
					if (debug && i == ptr) data[(ptrHeight + i) * dm.x + ptrWidth + p] = 166;
				}
			}
		}
		ptrWidth += maxWidth;
		if (ptrWidth + maxWidth > dm.x)
		{
			ptrWidth = 0;
			ptrHeight += maxHeight;
		}
	}
	Renderer::Texture* texture = device->createTexture(&Resource(total, dm.x, data), dm, Renderer::TextureFormat::R8_unorm);

	glm::vec2 maxCharDimensions;
	maxCharDimensions.x = maxWidth;
	maxCharDimensions.y = maxHeight;
	font = new Font(file, texture, characterInfos, glm::vec2(maxCharDimensions.x, maxCharDimensions.y), baseCharOffset, kerning);
	return font;
}