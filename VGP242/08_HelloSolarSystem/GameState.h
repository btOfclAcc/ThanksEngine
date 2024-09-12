#pragma once

#include <ThanksEngine/Inc/ThanksEngine.h>
#include <map>

class RenderItem
{
public:
	ThanksEngine::Graphics::MeshBuffer mMeshBuffer;
	ThanksEngine::Graphics::VertexShader mVertexShader;
	ThanksEngine::Graphics::PixelShader mPixelShader;
	ThanksEngine::Graphics::Texture mDiffuseTexture;
	ThanksEngine::Graphics::Sampler mSampler;

	void Terminate()
	{
		mSampler.Terminate();
		mDiffuseTexture.Terminate();
		mPixelShader.Terminate();
		mMeshBuffer.Terminate();
		mVertexShader.Terminate();
	}

	void Render()
	{
		mVertexShader.Bind();
		mPixelShader.Bind();

		mDiffuseTexture.BindPS(0);
		mSampler.BindPS(0);

		mMeshBuffer.Render();
	}
};

class GameState : public ThanksEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

protected:
	void UpdateCamera(float deltaTime);


	ThanksEngine::Graphics::Camera mCamera;
	ThanksEngine::Graphics::Camera mRenderTargetCamera;
	ThanksEngine::Graphics::ConstantBuffer mConstantBuffer;
	ThanksEngine::Graphics::RenderTarget mRenderTarget;

	RenderItem mSun;
	RenderItem mMercury;
	RenderItem mVenus;
	RenderItem mEarth;
	RenderItem mMars;
	RenderItem mJupiter;
	RenderItem mSaturn;
	RenderItem mUranus;
	RenderItem mNeptune;
	RenderItem mPluto;
};