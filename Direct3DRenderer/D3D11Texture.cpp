#include "D3D11Texture.h"

using namespace Renderer;
D3D11Texture::D3D11Texture(
	bool renderTarget,
	TextureFormat format,
	ID3D11Texture2D* texture,
	ID3D11ShaderResourceView* shaderView,
	const Uint2& dimensions,
	UINT arraySize
)
:Texture(renderTarget, dimensions,format, arraySize),
texture(texture),shaderView(shaderView)
{
	
}
