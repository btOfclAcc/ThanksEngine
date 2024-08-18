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
	mCamera.SetDirection({ 0.0f, 0.0f, 0.0f });

	mMeshBuffer.Initialize(mVertices.data(), sizeof(Vertex), mVertices.size());
	mConstantBuffer.Initialize(sizeof(Matrix4));

	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTransform.fx";
	mVertexShader.Initialize(shaderFile, VE_Position | VE_Color);

	//=====================================================
	// create a pixel shader
	//=====================================================

	auto device = GraphicsSystem::Get()->GetDevice();
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	HRESULT hr = D3DCompileFromFile(
		shaderFile.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS", "ps_5_0",
		shaderFlags, 0,
		&shaderBlob,
		&errorBlob);
	if (errorBlob != nullptr && errorBlob->GetBufferPointer() != nullptr)
	{
		LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
	}
	ASSERT(SUCCEEDED(hr), "Failed to compile pixel shader");

	hr = device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mPixelShader);
	ASSERT(SUCCEEDED(hr), "Failed to create pixel shader");
	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
}

void ShapeState::Terminate()
{
	mConstantBuffer.Terminate();
	mMeshBuffer.Terminate();
	mVertexShader.Terminate();
	mVertices.clear();
	SafeRelease(mPixelShader);
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

	// Pixel Shader
	auto context = GraphicsSystem::Get()->GetContext();
	context->PSSetShader(mPixelShader, nullptr, 0);

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