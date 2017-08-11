#include "MaterialProperty.h"
#include"Resource.h"

using namespace RenderFramework;
MaterialProperty::MaterialProperty(
	Renderer::GPUBuffer* buffer,UINT numConstants
)
:numConstants(numConstants),buffer(buffer),changed(false)
{
	constants = new MaterialConstant[numConstants];
}


MaterialProperty::~MaterialProperty()
{
	delete[] constants;
}


void MaterialProperty::setConstant(UINT index,const MaterialConstant& constant)
{
	if(index<numConstants)
	{
		constants[index] = constant;
		changed = true;
	}
}


void MaterialProperty::generateGPUBuffer()
{
	buffer->setData(
		&Resource(numConstants*sizeof(MaterialConstant),(char*)constants)
	);
	changed = false;
}
