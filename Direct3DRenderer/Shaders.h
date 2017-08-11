#ifndef SHADERS_HH
#define SHADERS_HH

#include<D3D11.h>
#include<D3DX11.h>
#include<string>
#include<list>
#include"Singleton.h"
#include"Manager.h"

struct PShader
{

	PShader();
	std::string name;
	ID3D11PixelShader* pixelShader;

};


struct VShader
{

	VShader();
	std::string name;
	ID3D11VertexShader* vertexShader;
	ID3D10Blob* shaderBlob;

};

struct GShader
{

	GShader();
	std::string name;
	ID3D11GeometryShader* geometryShader;
	ID3D10Blob* shaderBlob;

};


class ShaderManager
{

	std::list<PShader*> pshaders;
	std::list<VShader*> vshaders;
	std::list<GShader*> gshaders;

	PShader* loadPixelShader ( std::string filename );
	VShader* loadVertexShader( std::string filename );
	GShader* loadGeometryShader( std::string filename );

	public:

	PShader* getPixelShader( std::string name );
	VShader* getVertexShader( std::string name );
	GShader* getGeometryShader( std::string name );

};


#endif