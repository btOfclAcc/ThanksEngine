#pragma once

#include <ThanksEngine/Inc/ThanksEngine.h>
#include <vector>

class RenderItem
{
public:
	std::string mName;

	float mRotationPeriod;
	float mOrbitPeriod;

	float mRotationSpeed;
	float mTilt;
	float mDistanceFromSun;
	float mOrbitSpeed;

	float mRotation;
	float mOrbit;

	bool mShowOrbit = true;

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

	float mDeltaTime;
	float mTime;
	bool mShowGrid = false;

	ThanksEngine::Graphics::Camera mCamera;
	ThanksEngine::Graphics::Camera mRenderTargetCamera;
	ThanksEngine::Graphics::ConstantBuffer mConstantBuffer;
	ThanksEngine::Graphics::RenderTarget mRenderTarget;

	std::vector<RenderItem*> renderItems;

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
	RenderItem mSkySphere;
};