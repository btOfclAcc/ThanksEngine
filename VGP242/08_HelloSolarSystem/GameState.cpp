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

	mRenderTargetCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mRenderTargetCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	mRenderTargetCamera.SetAspectRatio(1.0f);

	constexpr uint32_t size = 512;
	mRenderTarget.Initialize(size, size, RenderTarget::Format::RGBA_U8);

	mConstantBuffer.Initialize(sizeof(Matrix4));

	MeshPX mesh;
	std::filesystem::path shaderFile;

	// Sun
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 109.0f);

		mSun.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mSun.mVertexShader.Initialize<VertexPX>(shaderFile);
		mSun.mPixelShader.Initialize(shaderFile);

		mSun.mDiffuseTexture.Initialize("../../Assets/Images/planets/sun.jpg");
		mSun.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}

	// Mercury
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 0.383f);

		mMercury.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mMercury.mVertexShader.Initialize<VertexPX>(shaderFile);
		mMercury.mPixelShader.Initialize(shaderFile);

		mMercury.mDiffuseTexture.Initialize("../../Assets/Images/planets/mercury.jpg");
		mMercury.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}

	// Venus
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 0.949f);

		mVenus.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mVenus.mVertexShader.Initialize<VertexPX>(shaderFile);
		mVenus.mPixelShader.Initialize(shaderFile);

		mVenus.mDiffuseTexture.Initialize("../../Assets/Images/planets/venus.jpg");
		mVenus.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}

	// Earth
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 1.0f);

		mEarth.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mEarth.mVertexShader.Initialize<VertexPX>(shaderFile);
		mEarth.mPixelShader.Initialize(shaderFile);

		mEarth.mDiffuseTexture.Initialize("../../Assets/Images/planets/earth/earth.jpg");
		mEarth.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}

	// Mars
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 0.532f);

		mMars.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mMars.mVertexShader.Initialize<VertexPX>(shaderFile);
		mMars.mPixelShader.Initialize(shaderFile);

		mMars.mDiffuseTexture.Initialize("../../Assets/Images/planets/mars.jpg");
		mMars.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}

	// Jupiter
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 11.21f);

		mJupiter.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mJupiter.mVertexShader.Initialize<VertexPX>(shaderFile);
		mJupiter.mPixelShader.Initialize(shaderFile);

		mJupiter.mDiffuseTexture.Initialize("../../Assets/Images/planets/jupiter.jpg");
		mJupiter.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}

	// Saturn
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 9.45f);

		mSaturn.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mSaturn.mVertexShader.Initialize<VertexPX>(shaderFile);
		mSaturn.mPixelShader.Initialize(shaderFile);

		mSaturn.mDiffuseTexture.Initialize("../../Assets/Images/planets/saturn.jpg");
		mSaturn.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}

	// Uranus
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 4.01f);

		mUranus.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mUranus.mVertexShader.Initialize<VertexPX>(shaderFile);
		mUranus.mPixelShader.Initialize(shaderFile);

		mUranus.mDiffuseTexture.Initialize("../../Assets/Images/planets/uranus.jpg");
		mUranus.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}

	// Neptune
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 3.88f);

		mNeptune.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mNeptune.mVertexShader.Initialize<VertexPX>(shaderFile);
		mNeptune.mPixelShader.Initialize(shaderFile);

		mNeptune.mDiffuseTexture.Initialize("../../Assets/Images/planets/neptune.jpg");
		mNeptune.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}

	// Pluto
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 0.186f);

		mPluto.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mPluto.mVertexShader.Initialize<VertexPX>(shaderFile);
		mPluto.mPixelShader.Initialize(shaderFile);

		mPluto.mDiffuseTexture.Initialize("../../Assets/Images/planets/pluto.jpg");
		mPluto.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}
}

void GameState::Terminate()
{
	mPluto.Terminate();
	mNeptune.Terminate();
	mUranus.Terminate();
	mSaturn.Terminate();
	mJupiter.Terminate();
	mMars.Terminate();
	mEarth.Terminate();
	mVenus.Terminate();
	mMercury.Terminate();
	mSun.Terminate();

	mConstantBuffer.Terminate();
	mRenderTarget.Terminate();
}

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

int target = 0;

void GameState::Render()
{
	// Constant Buffer
	Matrix4 matWorld = Matrix4::Identity;
	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);
	
	mSun.Render();
	matWorld = Matrix4::Identity;
	matWorld = Matrix4::RotationY(3.14f * 0.6f);
	matFinal = matWorld * matView * matProj;
	wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mMercury.Render();
	matWorld = Matrix4::Identity;
	matWorld = Matrix4::RotationY(3.14f * 0.2f) * Matrix4::Translation({ 0.0f, 0.0f, 9089.0f / 50.0f });
	matFinal = matWorld * matView * matProj;
	wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mVenus.Render();
	matWorld = Matrix4::Identity;
	matWorld = Matrix4::RotationY(3.14f * 0.4f) * Matrix4::Translation({ 0.0f, 0.0f, 16989.0f / 50.0f });
	matFinal = matWorld * matView * matProj;
	wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mEarth.Render();
	matWorld = Matrix4::Identity;
	matWorld = Matrix4::RotationY(3.14f * 0.6f) * Matrix4::Translation({ 0.0f, 0.0f, 23483.0f / 50.0f });
	matFinal = matWorld * matView * matProj;
	wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mMars.Render();
	matWorld = Matrix4::Identity;
	matWorld = Matrix4::RotationY(3.14f * 0.6f) * Matrix4::Translation({ 0.0f, 0.0f, 35772.0f / 50.0f });
	matFinal = matWorld * matView * matProj;
	wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mJupiter.Render();
	matWorld = Matrix4::Identity;
	matWorld = Matrix4::RotationY(3.14f * 0.6f) * Matrix4::Translation({ 0.0f, 0.0f, 122174.0f / 50.0f });
	matFinal = matWorld * matView * matProj;
	wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mSaturn.Render();
	matWorld = Matrix4::Identity;
	matWorld = Matrix4::RotationY(3.14f * 0.6f) * Matrix4::Translation({ 0.0f, 0.0f, 223867.0f / 50.0f });
	matFinal = matWorld * matView * matProj;
	wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mUranus.Render();
	matWorld = Matrix4::Identity;
	matWorld = Matrix4::RotationY(3.14f * 0.6f) * Matrix4::Translation({ 0.0f, 0.0f, 450409.0f / 50.0f });
	matFinal = matWorld * matView * matProj;
	wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mNeptune.Render();
	matWorld = Matrix4::Identity;
	matWorld = Matrix4::RotationY(3.14f * 0.6f) * Matrix4::Translation({ 0.0f, 0.0f, 705693.0f / 50.0f });
	matFinal = matWorld * matView * matProj;
	wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mPluto.Render();
	matWorld = Matrix4::Identity;
	matWorld = Matrix4::RotationY(3.14f * 0.6f) * Matrix4::Translation({ 0.0f, 0.0f, 926610.0f / 50.0f });
	matFinal = matWorld * matView * matProj;
	wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);


	matWorld = Matrix4::Identity;
	matView = mRenderTargetCamera.GetViewMatrix();
	matProj = mRenderTargetCamera.GetProjectionMatrix();
	matFinal = matWorld * matView * matProj;
	wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mRenderTarget.BeginRender();
	switch (target)
	{
		case 0: // Sun
			mSun.Render();
			break;
		
		case 1: // Mercury
			mMercury.Render();
			break;

		case 2: // Venus
			mVenus.Render();
			break;

		case 3: // Earth
			mEarth.Render();
			break;

		case 4: // Mars
			mMars.Render();
			break;

		case 5: // Jupiter
			mJupiter.Render();
			break;

		case 6: // Saturn
			mSaturn.Render();
			break;

		case 7: // Uranus
			mUranus.Render();
			break;

		case 8: // Neptune
			mNeptune.Render();
			break;

		case 9: // Pluto
			mPluto.Render();
			break;

		default:
			break;
	}
	mRenderTarget.EndRender();
}

bool buttonValye = false;
int intValue = 0;
void GameState::DebugUI()
{
	SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	SimpleDraw::Render(mCamera);

	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Just Some Test Text");
	ImGui::End();

	ImGui::Begin("Target Render", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	const char* items[] = { "Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto" };
	static const char* current_item = NULL;

	if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
	{
		for (int n = 0; n < IM_ARRAYSIZE(items); n++)
		{
			bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
			if (ImGui::Selectable(items[n], is_selected))
				current_item = items[n];
				target = n;
				if (is_selected)
					ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
		}
		ImGui::EndCombo();
	}

	ImGui::Image(
		mRenderTarget.GetRawData(),
		{ 256, 256 },
		{ 0, 0 },
		{ 1, 1 },
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 });
	ImGui::End();
}
