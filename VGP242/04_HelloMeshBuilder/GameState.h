#pragma once

#include <ThanksEngine/Inc/ThanksEngine.h>

class GameState : public ThanksEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	ThanksEngine::Graphics::Camera mCamera;
	ThanksEngine::Graphics::ConstantBuffer mConstantBuffer;
	ThanksEngine::Graphics::MeshBuffer mMeshBuffer;
	ThanksEngine::Graphics::VertexShader mVertexShader;
	ThanksEngine::Graphics::PixelShader mPixelShader;
	ThanksEngine::Graphics::Texture mDiffuseTexture;
	ThanksEngine::Graphics::Sampler mSampler;
};