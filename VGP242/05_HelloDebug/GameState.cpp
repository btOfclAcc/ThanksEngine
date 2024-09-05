#include "GameState.h"

using namespace ThanksEngine;
using namespace ThanksEngine::Math;
using namespace ThanksEngine::Graphics;
using namespace ThanksEngine::Core;
using namespace ThanksEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	MeshPX mesh = MeshBuilder::CreateSkySpherePX(30, 30, 100.0f);

	mMeshBuffer.Initialize<MeshPX>(mesh);
	mConstantBuffer.Initialize(sizeof(Matrix4));

	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexture.fx";
	mVertexShader.Initialize<VertexPX>(shaderFile);
	mPixelShader.Initialize(shaderFile);

	mDiffuseTexture.Initialize("../../Assets/Images/skysphere/space.jpg");
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void GameState::Terminate()
{
	mSampler.Terminate();
	mDiffuseTexture.Terminate();
	mPixelShader.Terminate();
	mConstantBuffer.Terminate();
	mMeshBuffer.Terminate();
	mVertexShader.Terminate();
}
float gRotationY = 0.0f;
float gRotationX = 0.0f;
void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
}

void GameState::UpdateCamera(float deltaTime)
{
	auto input = InputSystem::Get();
	const float moveSpeed = (input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f) * deltaTime;
	const float turnSpeed = 0.1f * deltaTime;
	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed);
	}
}

void GameState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	mDiffuseTexture.BindPS(0);
	mSampler.BindPS(0);

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

bool buttonValye = false;
int intValue = 0;
void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::LabelText("TestLable", "This is a test label!");
	ImGui::Spacing();
	ImGui::Checkbox("Test Checkbox", &buttonValye);
	ImGui::Separator();
	ImGui::DragInt("Test Drag Int", &intValue);
	if(ImGui::CollapsingHeader("Rotations"))
	{
		ImGui::Indent();
		ImGui::DragFloat("Rotation X", &gRotationX, 0.001f);
		ImGui::DragFloat("Rotation Y", &gRotationY, 0.001f);
		ImGui::Unindent();
	}
	ImGui::End();
}
