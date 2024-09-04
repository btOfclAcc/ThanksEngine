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
	void UpdateCamera(float deltaTime);

	virtual void CreateShape() {}

	ThanksEngine::Graphics::Camera mCamera;
	ThanksEngine::Graphics::ConstantBuffer mConstantBuffer;
	ThanksEngine::Graphics::MeshBuffer mMeshBuffer;
	ThanksEngine::Graphics::VertexShader mVertexShader;
	ThanksEngine::Graphics::PixelShader mPixelShader;
	ThanksEngine::Graphics::Texture mDiffuseTexture;
	ThanksEngine::Graphics::Sampler mSampler;
};

class CubeGameState : public GameState
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};

class RectGameState : public GameState
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};

class PlaneGameState : public GameState
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};

class SphereGameState : public GameState
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};

class CylinderGameState : public GameState
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};

class SkyBoxGameState : public GameState
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};

class SkySphereGameState : public GameState
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};