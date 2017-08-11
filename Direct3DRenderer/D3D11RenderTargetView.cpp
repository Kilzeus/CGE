#include "D3D11RenderTargetView.h"

using namespace Renderer;
D3D11RenderTargetView::D3D11RenderTargetView(
	ID3D11RenderTargetView* view
):view(view)
{
}