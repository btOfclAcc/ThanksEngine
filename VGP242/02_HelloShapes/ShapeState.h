#pragma once

#include <ThanksEngine/Inc/ThanksEngine.h>

class ShapeState : public ThanksEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Render() override;

protected:
	virtual void CreateShape() {}

	struct Vertex
	{
		ThanksEngine::Math::Vector3 position;
		ThanksEngine::Color color;
	};

	using Vertices = std::vector<Vertex>;
	Vertices mVertices;

	ID3D11Buffer* mVertexBuffer = nullptr;
	ID3D11VertexShader* mVertexShader = nullptr;
	ID3D11InputLayout* mInputLayout = nullptr;
	ID3D11PixelShader* mPixelShader = nullptr;
};

class TriangleShapeState : public ShapeState
{
public:
	void Update(float detlaTime) override;
protected:
	void CreateShape() override;
};

class DiamondShapeState : public ShapeState
{
public:
	void Update(float detlaTime) override;
protected:
	void CreateShape() override;
};

class HeartShapeState : public ShapeState
{
public:
	void Update(float detlaTime) override;
protected:
	void CreateShape() override;
};