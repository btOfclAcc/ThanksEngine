#pragma once

#include <ThanksEngine/Inc/ThanksEngine.h>

class ShapeState : public ThanksEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	virtual void CreateShape();

	struct Vertex
	{
		ThanksEngine::Math::Vector3 position;
		ThanksEngine::Color color;
	};

	using Vertices = std::vector<Vertex>;
	Vertices mVertices;

	ThanksEngine::Graphics::Camera mCamera;
	ThanksEngine::Graphics::ConstantBuffer mConstantBuffer;
	ThanksEngine::Graphics::MeshBuffer mMeshBuffer;
	ThanksEngine::Graphics::VertexShader mVertexShader;
	ThanksEngine::Graphics::PixelShader mPixelShader;
};