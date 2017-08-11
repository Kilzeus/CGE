#include "D3D11VertexShader.h"

using namespace Renderer;
D3D11VertexShader::D3D11VertexShader(
	VertexFormat* format,ID3D11VertexShader* shader
)
:VertexShader(format),shader(shader)
{
}
