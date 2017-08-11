#pragma once
#include "rendertargetview.h"
#include<d3d11.h>
namespace Renderer
{
	class D3D11RenderTargetView : public RenderTargetView
	{
		friend class D3D11Device;
		friend class D3D11RenderContext;
		ID3D11RenderTargetView* view;
		D3D11RenderTargetView(ID3D11RenderTargetView* view);
	public:
	};
}
