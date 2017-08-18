#include "TextureLoader.h"

using namespace AssetSystem;
UINT TextureLoader::instances = 0;
void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message) {
	printf("\n*** ");
	if(fif != FIF_UNKNOWN) {
	printf("%s Format\n", FreeImage_GetFormatFromFIF(fif));
	}
	printf(message);
	printf(" ***\n");
}


TextureLoader::TextureLoader(Renderer::Device* device)
	:device(device)
{
	if(!instances)
	{
		FreeImage_Initialise(false);
		FreeImage_SetOutputMessage(FreeImageErrorHandler);
	}
	instances++;
}


TextureLoader::~TextureLoader()
{
	if(instances==1)
		FreeImage_DeInitialise();
	instances--;
}


Renderer::Texture* TextureLoader::loadTexture(const std::string name)
{
	FIBITMAP* fiTexture = 0;
	Renderer::Texture* texture = 0;
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(name.c_str());

	fiTexture = FreeImage_Load(format,name.c_str());

	Renderer::Uint2 size;
	size.x = FreeImage_GetWidth(fiTexture);
	size.y = FreeImage_GetHeight(fiTexture);

	BYTE* bitmapData = 0;
	UINT bitsPerPixel = 0;
	bitsPerPixel = FreeImage_GetBPP(fiTexture);
	UINT pitch = FreeImage_GetPitch(fiTexture);
	bitmapData = new BYTE[size.x*size.y*4];
	FIBITMAP* fi32Tex = FreeImage_ConvertTo32Bits(fiTexture);
	FreeImage_Unload(fiTexture);
	//transorm pixel data so the picture is aligned properly and has 32 bbp
	//FreeImage_ConvertToRawBits(bitmapData,fi32Tex,pitch,bitsPerPixel,0xFF000000, 0x00FF0000, 0x0000FF00,true);
	FreeImage_ConvertToRawBits(bitmapData,fi32Tex,pitch,bitsPerPixel,FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK,true);	
	if(FreeImage_GetImageType(fi32Tex)==FIT_BITMAP)
	{
		texture = device->createTexture(&Resource(size.x*size.y*4,pitch,bitmapData),size,Renderer::B8G8R8A8_unorm);
	}

	FreeImage_Unload(fi32Tex);
	//delete[] bitmapData;
	return texture;
}
