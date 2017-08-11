#include "D3D11FragmentShader.h"

using namespace Renderer;
D3D11FragmentShader::D3D11FragmentShader(
	ID3D11PixelShader* shader
):shader(shader)
{
}
