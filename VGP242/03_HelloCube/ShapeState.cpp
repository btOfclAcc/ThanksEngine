#include "ShapeState.h"

using namespace ThanksEngine;
using namespace ThanksEngine::Math;
using namespace ThanksEngine::Graphics;
using namespace ThanksEngine::Core;
using namespace ThanksEngine::Input;

void ShapeState::CreateShape()
{
	// front
	mVertices.push_back({ {-0.5f,  -0.5f, -0.5f}, Colors::Red });
	mVertices.push_back({ {-0.5f,  0.5f, -0.5f}, Colors::Red });
	mVertices.push_back({ {0.5f,  0.5f, -0.5f}, Colors::Red });

	mVertices.push_back({ {-0.5f,  -0.5f, -0.5f}, Colors::Red });
	mVertices.push_back({ {0.5f,  0.5f, -0.5f}, Colors::Red });
	mVertices.push_back({ {0.5f,  -0.5f, -0.5f}, Colors::Red });

	// back
	mVertices.push_back({ {-0.5f,  -0.5f, 0.5f}, Colors::Red });
	mVertices.push_back({ {0.5f,  0.5f, 0.5f}, Colors::Red });
	mVertices.push_back({ {-0.5f,  0.5f, 0.5f}, Colors::Red });

	mVertices.push_back({ {-0.5f,  -0.5f, 0.5f}, Colors::Red });
	mVertices.push_back({ {0.5f,  -0.5f, 0.5f}, Colors::Red });
	mVertices.push_back({ {0.5f,  0.5f, 0.5f}, Colors::Red });

	// right
	mVertices.push_back({ {0.5f,  -0.5f, -0.5f}, Colors::Red });
	mVertices.push_back({ {0.5f,  0.5f, -0.5f}, Colors::Red });
	mVertices.push_back({ {0.5f,  0.5f, 0.5f}, Colors::Red });

	mVertices.push_back({ {0.5f,  -0.5f, -0.5f}, Colors::Red });
	mVertices.push_back({ {0.5f,  0.5f, 0.5f}, Colors::Red });
	mVertices.push_back({ {0.5f,  -0.5f, 0.5f}, Colors::Red });

	// left
	mVertices.push_back({ {-0.5f,  -0.5f, -0.5f}, Colors::Red });
	mVertices.push_back({ {-0.5f,  0.5f, 0.5f}, Colors::Red });
	mVertices.push_back({ {-0.5f,  0.5f, -0.5f}, Colors::Red });
						   
	mVertices.push_back({ {-0.5f,  -0.5f, -0.5f}, Colors::Red });
	mVertices.push_back({ {-0.5f,  -0.5f, 0.5f}, Colors::Red });
	mVertices.push_back({ {-0.5f,  0.5f, 0.5f}, Colors::Red });

	// top
	mVertices.push_back({ {-0.5f,  0.5f, -0.5f}, Colors::Red });
	mVertices.push_back({ {-0.5f,  0.5f, 0.5f}, Colors::Red });
	mVertices.push_back({ {0.5f,  0.5f, 0.5f}, Colors::Red });

	mVertices.push_back({ {-0.5f,  0.5f, -0.5f}, Colors::Red });
	mVertices.push_back({ {0.5f,  0.5f, 0.5f}, Colors::Red });
	mVertices.push_back({ {0.5f,  0.5f, -0.5f}, Colors::Red });

	// bottom
	mVertices.push_back({ {-0.5f,  -0.5f, -0.5f}, Colors::Red });
	mVertices.push_back({ {0.5f,  -0.5f, 0.5f}, Colors::Red });
	mVertices.push_back({ {-0.5f,  -0.5f, 0.5f}, Colors::Red });

	mVertices.push_back({ {-0.5f,  -0.5f, -0.5f}, Colors::Red });
	mVertices.push_back({ {0.5f,  -0.5f, -0.5f}, Colors::Red });
	mVertices.push_back({ {0.5f,  -0.5f, 0.5f}, Colors::Red });
}

void ShapeState::Initialize()
{
	CreateShape();

	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mMeshBuffer.Initialize(mVertices.data(), sizeof(Vertex), mVertices.size());
	mConstantBuffer.Initialize(sizeof(Matrix4));

	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTransform.fx";
	mVertexShader.Initialize(shaderFile, VE_Position | VE_Color);
	mPixelShader.Initialize(shaderFile);

}

void ShapeState::Terminate()
{
	mPixelShader.Terminate();
	mConstantBuffer.Terminate();
	mMeshBuffer.Terminate();
	mVertexShader.Terminate();
	mVertices.clear();
}
float gRotationY = 0.0f;
float gRotationX = 0.0f;
void ShapeState::Update(float deltaTime)
{
	gRotationY += Math::Constants::HalfPi * deltaTime * 0.5f;
	gRotationX += Math::Constants::HalfPi * deltaTime * 0.25f;
}

void ShapeState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	// Constant Buffer
	Matrix4 matWorld = Matrix4::RotationY(gRotationY) * Matrix4::RotationX(gRotationX);
	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);
	mMeshBuffer.Render();
}