#pragma once
#include "texture.h"
#include<d3d11.h>
namespace Renderer
{
	class D3D11Texture : public Texture
	{
		friend class D3D11Device;
		friend class D3D11RenderContext;
		ID3D11Texture2D* texture;
		ID3D11ShaderResourceView* shaderView;
		D3D11_USAGE usage;

		D3D11Texture(
			bool renderTarget,
			TextureFormat format,
			ID3D11Texture2D* texture,
			ID3D11ShaderResourceView* shaderView,
			const Uint2& dimensions,
			UINT arraySize
		);
		public:
	};
}
