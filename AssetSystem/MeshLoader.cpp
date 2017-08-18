#include "MeshLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include"EffectLoader.h"
#include"TextureLoader.h"
#include <iostream>


using namespace AssetSystem;
MeshLoader::MeshLoader()
{
}


Mesh* MeshLoader::loadMesh(Renderer::Device* device, std::string filename)
{
	Mesh* mesh = new Mesh;
	Assimp::Importer importer;
	AssetSystem::TextureLoader* textureLoader = new AssetSystem::TextureLoader(device);

	const aiScene* scene = importer.ReadFile(filename, 
		aiProcess_GenNormals |
		aiProcess_CalcTangentSpace |
		aiProcess_FlipUVs |
		//aiProcess_FindDegenerates |
		aiProcess_Triangulate
	);
	if (!scene)
	{
		std::cerr << "assimp error when importing mesh " << filename;
		return 0;
	}
	if (scene->HasMeshes())
	{
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			MeshPart* meshpart = new MeshPart;
			aiMesh* aiMesh = scene->mMeshes[i];
			if (!aiMesh->HasPositions() || !aiMesh->HasFaces())
			{
				std::cerr << "no positions or faces in mesh " << filename;
				continue;
			}
			MeshVertex* vertices = new MeshVertex[aiMesh->mNumVertices];
			for (int p = 0; p < aiMesh->mNumVertices; p++)
			{
				vertices[p].position.x = aiMesh->mVertices[p].x;
				vertices[p].position.y = aiMesh->mVertices[p].y;
				vertices[p].position.z = aiMesh->mVertices[p].z;
				if (aiMesh->HasNormals())
				{
					vertices[p].normal.x = aiMesh->mNormals[p].x;
					vertices[p].normal.y = aiMesh->mNormals[p].y;
					vertices[p].normal.z = aiMesh->mNormals[p].z;
				}
				if (aiMesh->HasTangentsAndBitangents())
				{
					vertices[p].tangent.x = aiMesh->mTangents[p].x;
					vertices[p].tangent.y = aiMesh->mTangents[p].y;
					vertices[p].tangent.z = aiMesh->mTangents[p].z;
					vertices[p].bitangent.x = aiMesh->mBitangents[p].x;
					vertices[p].bitangent.y = aiMesh->mBitangents[p].y;
					vertices[p].bitangent.z = aiMesh->mBitangents[p].z;
					
				}
				if (aiMesh->HasTextureCoords(0))
				{
					vertices[p].uv.x = aiMesh->mTextureCoords[0][p].x;
				/*	while (vertices[p].uv.x > 1.f) vertices[p].uv.x -= 1.f;
					if (vertices[p].uv.x < 0.f)
					{
						while (vertices[p].uv.x < 0.f) 
							vertices[p].uv.x += 1.f;
						//vertices[p].uv.x = 1.f - vertices[p].uv.x;
					}*/
					//vertices[p].uv.x = 1.f - vertices[p].uv.x;
					vertices[p].uv.y = aiMesh->mTextureCoords[0][p].y;
				/*	while (vertices[p].uv.y > 1.f) vertices[p].uv.y -= 1.f;
					if (vertices[p].uv.y < 0.f)
					{
						while (vertices[p].uv.y < 0.f) 
							vertices[p].uv.y += 1.f;
						//vertices[p].uv.y = 1.f - vertices[p].uv.y;
					}*/
					//vertices[p].uv.y = 1.f - vertices[p].uv.y;
					//vertices[p].uv.y = 1.f - vertices[p].uv.y;
					/*if (vertices[p].uv.x < 0.f) vertices[p].uv.x = -vertices[p].uv.x;
					/if (vertices[p].uv.y < 0.f || vertices[p].uv.y > 1.f) vertices[p].uv.y = -vertices[p].uv.y;*/

				}
			}
			//create vertexbuffer
			UINT datasize = sizeof(AssetSystem::MeshVertex)*aiMesh->mNumVertices;
			meshpart->vertexBuffer = device->crateVertexBuffer(datasize);
			meshpart->vertexBuffer->setNumVertices(aiMesh->mNumVertices);
			meshpart->vertexBuffer->setVertexByteSize(sizeof(AssetSystem::MeshVertex));
			meshpart->vertexBuffer->setData(&Resource(datasize, vertices), aiMesh->mNumVertices, sizeof(AssetSystem::MeshVertex));

			const aiMaterial* mat = scene->mMaterials[aiMesh->mMaterialIndex];
			aiString  tex(" ");

			meshpart->material = new RenderFramework::Material();
			Renderer::Texture* texture = 0;
			int numTex = 0;
			while(tex.length > 0)
			{
				if (AI_SUCCESS != mat->GetTexture(aiTextureType_DIFFUSE, numTex, &tex, 0, 0, 0, 0, 0))
					break;
				texture = textureLoader->loadTexture(tex.C_Str());
				meshpart->material->setTexture(numTex, texture);
				numTex++;
			}
			texture = textureLoader->loadTexture("armorHull1normal.png");
			meshpart->material->setTexture(1, texture);

			RenderFramework::EffectLoader loader;
			RenderFramework::EffectGroup* effectGroup = loader.loadEffect(device, "gbuffer.fx");
			meshpart->material->setRenderEffect(effectGroup->getEffect("normalmapped"));
			mesh->meshParts.push_back(meshpart);
		}
	}
	//RenderFramework::EffectGroup* effectGroup = loader.loadEffect(device, "basic.fx");
	return mesh;
}
