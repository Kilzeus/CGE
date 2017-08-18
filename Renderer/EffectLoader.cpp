#include"EffectLoader.h"
#include"VertexShader.h"
#include<Windows.h>

using namespace RenderFramework;
EffectGroup* EffectLoader::loadEffect(
	Renderer::Device* device,std::string filename
)
{
	TiXmlDocument doc( filename.c_str());
	bool success = doc.LoadFile();
	if (!success)
	{
		return 0;
	}
	TiXmlHandle docHandle( &doc );
	TiXmlElement* element = docHandle.FirstChild().ToElement();
	TiXmlAttribute* attribute = 0;
	EffectGroup* group = 0;

	element = element->FirstChildElement();
	while(element)
	{
		if(element->ValueStr() == "effect_group")
		{
			attribute = element->FirstAttribute();
			if (std::string(attribute->Name()) == "name")
				group = new EffectGroup(attribute->ValueStr());

			TiXmlElement* effectElement = element->FirstChildElement();
			while (effectElement)
			{
				std::string effectName;
				RenderEffect* effect = 0;
				Renderer::VertexShader* vertexShader = 0;
				Renderer::FragmentShader* fragmentShader = 0;
				Renderer::GeometryShader* geometryShader = 0;
				if (effectElement->ValueStr() == "effect")
				{
					attribute = effectElement->FirstAttribute();
					if (attribute->NameTStr() == "name")
						effectName = attribute->ValueStr();
					TiXmlElement* shaderElement = effectElement->FirstChildElement();
					Resource* shader = 0;
					Renderer::VertexFormat* format = device->createVertexFormat();
					while (shaderElement)
					{
						if (shaderElement->ValueStr() == "vertex_format")
						{
							TiXmlElement* vertexElementNode = shaderElement->FirstChildElement();
							UINT index = 0;
							while (vertexElementNode)
							{
								if (vertexElementNode->ValueStr() == "vertex_element")
								{
									attribute = vertexElementNode->FirstAttribute();
									std::string semantic, typeStr;
									UINT slot = 0;
									bool instanceData = 0;
									while (attribute)
									{
										if (std::string(attribute->Name()) == "semantic")
											semantic = attribute->ValueStr();
										if (std::string(attribute->Name()) == "type")
											typeStr = attribute->ValueStr();
										if (std::string(attribute->Name()) == "index")
											slot = atoi(attribute->Value());
										if (std::string(attribute->Name()) == "instanceData")
											instanceData = atoi(attribute->Value());
										attribute = attribute->Next();
									}
									Renderer::VertexElementType type = Renderer::FLOAT4;
									if (typeStr == "Float1") type = Renderer::FLOAT1;
									if (typeStr == "Float2") type = Renderer::FLOAT2;
									if (typeStr == "Float3") type = Renderer::FLOAT3;
									if (typeStr == "Float4") type = Renderer::FLOAT4;
									if (typeStr == "Int1") type = Renderer::Int1;
									if (typeStr == "Int2") type = Renderer::Int2;
									if (typeStr == "Int3") type = Renderer::Int3;
									if (typeStr == "Int4") type = Renderer::Int4;

									format->addElement(Renderer::VertexElement(
										semantic, type, slot, instanceData
										));
								}
								index++;
								vertexElementNode = vertexElementNode->NextSiblingElement();
							}
						}

						if (shaderElement->ValueStr() == "vertex_shader" ||
							shaderElement->ValueStr() == "fragment_shader" ||
							shaderElement->ValueStr() == "geometry_shader"
							)
						{
							attribute = shaderElement->FirstAttribute();
							std::string shaderProfile;
							std::wstring shaderFile;
							if (std::string(attribute->Name()) == "profile")
								shaderProfile = attribute->ValueStr();
							attribute = attribute->Next();
							if (std::string(attribute->Name()) == "file")
								shaderFile.assign(
								attribute->ValueStr().begin(), attribute->ValueStr().end());
							shader = device->compileShaderFromFile(
								shaderFile, shaderProfile
								);
						}
						if (shaderElement->ValueStr() == "vertex_shader")
							vertexShader = device->createVertexShader(
							shader, format
							);
						if (shaderElement->ValueStr() == "fragment_shader")
							fragmentShader = device->createFragmentShader(shader);
						if (shaderElement->ValueStr() == "geometry_shader")
							geometryShader = device->createGeometryShader(shader);
						shaderElement = shaderElement->NextSiblingElement();
					}
				}
				effect = new RenderEffect(effectName, vertexShader, fragmentShader, geometryShader);
				if (group) group->addEffect(effectName, effect);
				effectElement = effectElement->NextSiblingElement();
			}
		}
		element = element->NextSiblingElement();
	}
	return group;
}