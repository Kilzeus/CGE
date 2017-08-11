#include"Material.h"

using namespace RenderFramework;
Material::Material()
	:materialProperties(0)
{
}
void Material::setMaterialProperties(
	MaterialProperty* materialProperties
)
{
	this->materialProperties = materialProperties;
}


void Material::setRenderEffect(RenderEffect* effect)
{
	vertexShader = effect->getVertexShader();
	fragmentShader = effect->getFragmentShader();
	geometryShader = effect->getGeometryShader();
	//this->effect = effect;
}


UINT Material::getNumTextures() const
{
	return textures.size();
}


Renderer::Texture* Material::getTexture(UINT index)
{
	return textures[index];
}


void Material::setMaterial(Renderer::RenderContext* context)
{
	context->setVertexFormat(vertexShader->getVertexFormat());
	context->setVertexShader(vertexShader);
	context->setFragmentShader(fragmentShader);
	if(geometryShader) context->setGeometryShader(geometryShader);
	for(int i=0;i<textures.size();i++)
	{
		context->setTexture(i,textures[i]);
	}
	if(materialProperties)
		if(materialProperties->changed)
			materialProperties->generateGPUBuffer();
}


void Material::setTexture(UINT index,Renderer::Texture* texture)
{
	if(index >= textures.size()) textures.resize(index+1);
	textures[index] = texture;
}