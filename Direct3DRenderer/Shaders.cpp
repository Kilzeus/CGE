#include"Shaders.h"
#include"DeferredRenderer.h"
#include"Logger.h"

PShader::PShader ()
{

}


VShader::VShader ()
{

}

GShader::GShader()
{

}


PShader* ShaderManager::getPixelShader( std::string name )
{

	if(!this->pshaders.empty()) 
	{
		std::list<PShader*>::iterator iter = this->pshaders.begin();
		while( iter != this->pshaders.end())
		{
			if((*iter)->name == name ) return *iter;
			iter++;
		}
	}
	return loadPixelShader( name );

}


VShader* ShaderManager::getVertexShader( std::string name )
{

	if(!this->vshaders.empty()) 
	{
		std::list<VShader*>::iterator iter = this->vshaders.begin ();
		while( iter != this->vshaders.end ())
		{
			if((*iter)->name == name) return *iter;
			iter++;

		}
	}
	return loadVertexShader( name );

}

GShader* ShaderManager::getGeometryShader( std::string name )
{

	if(!this->gshaders.empty()) 
	{
		std::list<GShader*>::iterator iter = this->gshaders.begin ();
		while( iter != this->gshaders.end ())
		{
			if((*iter)->name == name) return *iter;
			iter++;

		}
	}
	return loadGeometryShader( name );
}

GShader* ShaderManager::loadGeometryShader( std::string filename )
{

	ID3D10Blob* pShader;
	ID3D10Blob* pErrors;
	GShader* current_shader = new GShader;

	if(FAILED(D3DX11CompileFromFile ( filename.c_str(), 0, 0, "gs_main", "gs_4_1", D3D10_SHADER_ENABLE_STRICTNESS, 0, 0, &pShader, &pErrors, 0 ))) //D3D10_SHADER_ENABLE_STRICTNESS
	{ 
		std::string error( (char*)pErrors->GetBufferPointer());
		Logger::getSingleton().logEntry( "Shader loading", error );
	}

	if(FAILED(DeferredRenderer::getSingleton().getDevice()->CreateGeometryShader ( pShader->GetBufferPointer(), pShader->GetBufferSize(), 0, &current_shader->geometryShader )))
	{
		MessageBox ( 0,"Failed to create geometryshader", "ERROR", MB_OK );
	}
	current_shader->name = filename;
	pShader->Release();
	return current_shader;

}

PShader* ShaderManager::loadPixelShader( std::string filename )
{

	ID3D10Blob* pShader;
	ID3D10Blob* pErrors;

	PShader* current_shader = new PShader;

	if(FAILED(D3DX11CompileFromFile ( filename.c_str(), 0, 0, "ps_main", "ps_4_1", D3D10_SHADER_ENABLE_STRICTNESS, 0, 0, &pShader, &pErrors, 0 ))) //D3D10_SHADER_ENABLE_STRICTNESS
	{ 
		std::string error( (char*)pErrors->GetBufferPointer());
		Logger::getSingleton().logEntry( "Shader loading", error );
	}

	if(FAILED(DeferredRenderer::getSingleton().getDevice()->CreatePixelShader ( pShader->GetBufferPointer(), pShader->GetBufferSize(), 0, &current_shader->pixelShader )))
	{
		MessageBox ( 0,"Failed to create pixelshader", "ERROR", MB_OK );
	}
	current_shader->name = filename;

/*	D3D11_INPUT_ELEMENT_DESC inputDesc[]={{
	"SV_POSITION",
	0,
	DXGI_FORMAT_R32G32_FLOAT,
	0,
	D3D11_APPEND_ALIGNED_ELEMENT,
	D3D11_INPUT_PER_VERTEX_DATA,
	0 }};

	if(FAILED(DeferredRenderer::getSingleton().getDevice()->CreateInputLayout ( inputDesc, 1, pShader->GetBufferPointer(), pShader->GetBufferSize(), &current_shader->InputLayout )))
		MessageBox ( 0, "Failed to create inputlayout", "ERROR", MB_OK );
*/
	pShader->Release();

	return current_shader;

}
 

VShader* ShaderManager::loadVertexShader( std::string filename )
{

	ID3D10Blob* pErrors;
	VShader* shader = new VShader;

	if(FAILED(D3DX11CompileFromFile ( filename.c_str(), 0, 0, "vs_main", "vs_4_1", D3D10_SHADER_ENABLE_STRICTNESS, 0, 0, &shader->shaderBlob, &pErrors, 0 )))
	{
		std::string error( (char*)pErrors->GetBufferPointer());
		Logger::getSingleton().logEntry( "Shader loading", error );
	}

	if(FAILED(DeferredRenderer::getSingleton().getDevice()->CreateVertexShader ( shader->shaderBlob->GetBufferPointer(), shader->shaderBlob->GetBufferSize(), NULL, &shader->vertexShader )))
	{
		MessageBox ( 0, "Failed to create vertexshader", "ERROR", MB_OK );
	}
	shader->name = filename;
	return shader;
}

