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

	float mRadius;

	bool mShowOrbit = true;

	ThanksEngine::Graphics::MeshBuffer mMeshBuffer;
	ThanksEngine::Graphics::Texture mDiffuseTexture;

	void Terminate()
	{
		mDiffuseTexture.Terminate();
		mMeshBuffer.Terminate();
	}

	void Render()
	{
		mDiffuseTexture.BindPS(0);
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
	int mTarget = 0;

	ThanksEngine::Graphics::Camera mCamera;
	ThanksEngine::Graphics::Camera mRenderTargetCamera;
	ThanksEngine::Graphics::ConstantBuffer mConstantBuffer;
	ThanksEngine::Graphics::RenderTarget mRenderTarget;

	ThanksEngine::Graphics::VertexShader mVertexShader;
	ThanksEngine::Graphics::PixelShader mPixelShader;
	ThanksEngine::Graphics::Sampler mSampler;

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