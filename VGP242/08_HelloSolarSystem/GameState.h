#pragma once

#include <ThanksEngine/Inc/ThanksEngine.h>

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


	ThanksEngine::Graphics::MeshBuffer mMeshBufferSun;
	ThanksEngine::Graphics::VertexShader mVertexShaderSun;
	ThanksEngine::Graphics::PixelShader mPixelShaderSun;
	ThanksEngine::Graphics::Texture mDiffuseTextureSun;
	ThanksEngine::Graphics::Sampler mSamplerSun;


	ThanksEngine::Graphics::MeshBuffer mMeshBufferMercury;
	ThanksEngine::Graphics::VertexShader mVertexShaderMercury;
	ThanksEngine::Graphics::PixelShader mPixelShaderMercury;
	ThanksEngine::Graphics::Texture mDiffuseTextureMercury;
	ThanksEngine::Graphics::Sampler mSamplerMercury;


	ThanksEngine::Graphics::MeshBuffer mMeshBufferVenus;
	ThanksEngine::Graphics::VertexShader mVertexShaderVenus;
	ThanksEngine::Graphics::PixelShader mPixelShaderVenus;
	ThanksEngine::Graphics::Texture mDiffuseTextureVenus;
	ThanksEngine::Graphics::Sampler mSamplerVenus;


	ThanksEngine::Graphics::MeshBuffer mMeshBufferEarth;
	ThanksEngine::Graphics::VertexShader mVertexShaderEarth;
	ThanksEngine::Graphics::PixelShader mPixelShaderEarth;
	ThanksEngine::Graphics::Texture mDiffuseTextureEarth;
	ThanksEngine::Graphics::Sampler mSamplerEarth;


	ThanksEngine::Graphics::MeshBuffer mMeshBufferMars;
	ThanksEngine::Graphics::VertexShader mVertexShaderMars;
	ThanksEngine::Graphics::PixelShader mPixelShaderMars;
	ThanksEngine::Graphics::Texture mDiffuseTextureMars;
	ThanksEngine::Graphics::Sampler mSamplerMars;


	ThanksEngine::Graphics::MeshBuffer mMeshBufferJupiter;
	ThanksEngine::Graphics::VertexShader mVertexShaderJupiter;
	ThanksEngine::Graphics::PixelShader mPixelShaderJupiter;
	ThanksEngine::Graphics::Texture mDiffuseTextureJupiter;
	ThanksEngine::Graphics::Sampler mSamplerJupiter;


	ThanksEngine::Graphics::MeshBuffer mMeshBufferSaturn;
	ThanksEngine::Graphics::VertexShader mVertexShaderSaturn;
	ThanksEngine::Graphics::PixelShader mPixelShaderSaturn;
	ThanksEngine::Graphics::Texture mDiffuseTextureSaturn;
	ThanksEngine::Graphics::Sampler mSamplerSaturn;


	ThanksEngine::Graphics::MeshBuffer mMeshBufferUranus;
	ThanksEngine::Graphics::VertexShader mVertexShaderUranus;
	ThanksEngine::Graphics::PixelShader mPixelShaderUranus;
	ThanksEngine::Graphics::Texture mDiffuseTextureUranus;
	ThanksEngine::Graphics::Sampler mSamplerUranus;


	ThanksEngine::Graphics::MeshBuffer mMeshBufferNeptune;
	ThanksEngine::Graphics::VertexShader mVertexShaderNeptune;
	ThanksEngine::Graphics::PixelShader mPixelShaderNeptune;
	ThanksEngine::Graphics::Texture mDiffuseTextureNeptune;
	ThanksEngine::Graphics::Sampler mSamplerNeptune;


	ThanksEngine::Graphics::MeshBuffer mMeshBufferPluto;
	ThanksEngine::Graphics::VertexShader mVertexShaderPluto;
	ThanksEngine::Graphics::PixelShader mPixelShaderPluto;
	ThanksEngine::Graphics::Texture mDiffuseTexturePluto;
	ThanksEngine::Graphics::Sampler mSamplerPluto;
};