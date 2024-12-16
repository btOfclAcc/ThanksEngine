#pragma once

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "Sampler.h"

namespace ThanksEngine::Graphics
{
	class RenderObject;
	class Texture;

	class CRTEffect
	{
	public:

		void Initialize(const std::filesystem::path& filePath);
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);

		void SetTexture(const Texture* texture, uint32_t slot = 0);

		void ChangeTime(float deltaTime);

		void DebugUI();

	private:
		struct SettingsData
		{
			float param0 = 0.0f;
			float param1 = 0.0f;
			float param2 = 0.0f;
			float param3 = 0.0f;
		};

		using CRTBuffer = TypedConstantBuffer<SettingsData>;
		CRTBuffer mCRTBuffer;

		VertexShader mVertexShader;
		PixelShader mPixelShader;
		Sampler mSampler;
		std::array<const Texture*, 4> mTextures;

		float mBlurStrength = 1.0f;

		float mTime = 0.0f;

		float mCurvature = 0.15f;
		float mScanlineFrequency = 200.0f;
	};
}