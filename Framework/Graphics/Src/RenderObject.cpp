#include "Precompiled.h"
#include "RenderObject.h"
#include "Model.h"

using namespace ThanksEngine;
using namespace ThanksEngine::Graphics;

void RenderObject::Terminate()
{
	meshBuffer.Terminate();
}

void RenderGroup::Initialize(const std::filesystem::path& modelFilePath)
{
	modelId = ModelCache::Get()->LoadModel(modelFilePath);
	const Model* model = ModelCache::Get()->GetModel(modelId);
	ASSERT(model != nullptr, "RenderGroup: model %s did not load", modelFilePath.u8string().c_str());
	Initialize(*model);
}

void RenderGroup::Initialize(const Model& model)
{
	auto TryLoadTexture = [](const auto& textureName)->TextureId
		{
			if (textureName.empty())
			{
				return 0;
			}

			return TextureCache::Get()->LoadTexture(textureName, false);
		};

	for (const Model::MeshData& meshData : model.meshData)
	{
		RenderObject& renderObject = renderObjects.emplace_back();
		renderObject.meshBuffer.Initialize(meshData.mesh);
		if (meshData.materialIndex < model.materialData.size())
		{
			const Model::MaterialData& materialData = model.materialData[meshData.materialIndex];
			renderObject.material = materialData.material;
			renderObject.diffuseMapId = TryLoadTexture(materialData.diffuseMapName);
			renderObject.normalMapId = TryLoadTexture(materialData.normalMapName);
			renderObject.specMapId = TryLoadTexture(materialData.specMapName);
			renderObject.bumpMapId = TryLoadTexture(materialData.bumpMapName);
		}
	}
}

void RenderGroup::Terminate()
{
	for (RenderObject& renderObject : renderObjects)
	{
		renderObject.Terminate();
	}
}