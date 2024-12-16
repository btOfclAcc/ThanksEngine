#include "Precompiled.h"
#include "CRTEffect.h"

#include "GraphicsSystem.h"
#include "RenderObject.h"
#include "Texture.h"
#include "VertexTypes.h"

using namespace ThanksEngine;
using namespace ThanksEngine::Graphics;

void CRTEffect::Initialize(const std::filesystem::path& filePath)
{
	mVertexShader.Initialize<VertexPX>(filePath);
	mPixelShader.Initialize(filePath);
	mSampler.Initialize(Sampler::Filter::Point, Sampler::AddressMode::Wrap);
	mCRTBuffer.Initialize();
}

void CRTEffect::Terminate()
{
	mCRTBuffer.Terminate();
	mSampler.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
}

void CRTEffect::Begin()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mSampler.BindPS(0);

	for (uint32_t i = 0; i < mTextures.size(); ++i)
	{
		if (mTextures[i] != nullptr)
		{
			mTextures[i]->BindPS(i);
		}
	}

	GraphicsSystem* gs = GraphicsSystem::Get();
	const float screenWidth = gs->GetBackBufferWidth();

	SettingsData data;
	data.param0 = mBlurStrength / screenWidth;
	data.param1 = mTime;
	data.param2 = mCurvature;
	data.param3 = mScanlineFrequency;

	mCRTBuffer.Update(data);
	mCRTBuffer.BindPS(0);
}

void CRTEffect::End()
{
	for (uint32_t i = 0; i < mTextures.size(); ++i)
	{
		Texture::UnbindPS(i);
	}
}

void CRTEffect::Render(const RenderObject& renderObject)
{
	renderObject.meshBuffer.Render();
}

void CRTEffect::SetTexture(const Texture* texture, uint32_t slot)
{
	ASSERT(slot < mTextures.size(), "CRTEffect: invalid slot index");
	mTextures[slot] = texture;
}

void CRTEffect::ChangeTime(float deltaTime)
{
	mTime += deltaTime;
}

void CRTEffect::DebugUI()
{
	if (ImGui::CollapsingHeader("CRTEffect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("BlurStrength", &mBlurStrength, 0.1f, 0.0f, 100.0f);
		ImGui::DragFloat("Curvature ", &mCurvature, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat("Scanline Frequency", &mScanlineFrequency, 1.0f, 0.0f, 1000.0f);
	}
}
