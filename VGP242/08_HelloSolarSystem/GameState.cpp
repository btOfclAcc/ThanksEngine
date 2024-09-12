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

		mMeshBufferSun.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mVertexShaderSun.Initialize<VertexPX>(shaderFile);
		mPixelShaderSun.Initialize(shaderFile);

		mDiffuseTextureSun.Initialize("../../Assets/Images/planets/sun.jpg");
		mSamplerSun.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}

	// Mercury
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 0.33f);

		mMeshBufferMercury.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mVertexShaderMercury.Initialize<VertexPX>(shaderFile);
		mPixelShaderMercury.Initialize(shaderFile);

		mDiffuseTextureMercury.Initialize("../../Assets/Images/planets/mercury.jpg");
		mSamplerMercury.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}

	// Venus
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 1.0f);

		mMeshBufferVenus.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mVertexShaderVenus.Initialize<VertexPX>(shaderFile);
		mPixelShaderVenus.Initialize(shaderFile);

		mDiffuseTextureVenus.Initialize("../../Assets/Images/planets/venus.jpg");
		mSamplerVenus.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}

	// Earth
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 1.0f);

		mMeshBufferEarth.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mVertexShaderEarth.Initialize<VertexPX>(shaderFile);
		mPixelShaderEarth.Initialize(shaderFile);

		mDiffuseTextureEarth.Initialize("../../Assets/Images/planets/earth/earth.jpg");
		mSamplerEarth.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}

	// Mars
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 0.5f);

		mMeshBufferMars.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mVertexShaderMars.Initialize<VertexPX>(shaderFile);
		mPixelShaderMars.Initialize(shaderFile);

		mDiffuseTextureMars.Initialize("../../Assets/Images/planets/mars.jpg");
		mSamplerMars.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}

	// Jupiter
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 11.0f);

		mMeshBufferJupiter.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mVertexShaderJupiter.Initialize<VertexPX>(shaderFile);
		mPixelShaderJupiter.Initialize(shaderFile);

		mDiffuseTextureJupiter.Initialize("../../Assets/Images/planets/jupiter.jpg");
		mSamplerJupiter.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}

	// Saturn
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 9.0f);

		mMeshBufferSaturn.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mVertexShaderSaturn.Initialize<VertexPX>(shaderFile);
		mPixelShaderSaturn.Initialize(shaderFile);

		mDiffuseTextureSaturn.Initialize("../../Assets/Images/planets/saturn.jpg");
		mSamplerSaturn.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}

	// Uranus
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 4.0f);

		mMeshBufferUranus.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mVertexShaderUranus.Initialize<VertexPX>(shaderFile);
		mPixelShaderUranus.Initialize(shaderFile);

		mDiffuseTextureUranus.Initialize("../../Assets/Images/planets/uranus.jpg");
		mSamplerUranus.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}

	// Neptune
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 4.0f);

		mMeshBufferNeptune.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mVertexShaderNeptune.Initialize<VertexPX>(shaderFile);
		mPixelShaderNeptune.Initialize(shaderFile);

		mDiffuseTextureNeptune.Initialize("../../Assets/Images/planets/neptune.jpg");
		mSamplerNeptune.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}

	// Pluto
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, 0.16f);

		mMeshBufferPluto.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mVertexShaderPluto.Initialize<VertexPX>(shaderFile);
		mPixelShaderPluto.Initialize(shaderFile);

		mDiffuseTexturePluto.Initialize("../../Assets/Images/planets/pluto.jpg");
		mSamplerPluto.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}
}

void GameState::Terminate()
{
	// Pluto
	{
		mSamplerPluto.Terminate();
		mDiffuseTexturePluto.Terminate();
		mPixelShaderPluto.Terminate();
		mMeshBufferPluto.Terminate();
		mVertexShaderPluto.Terminate();
	}

	// Neptune
	{
		mSamplerNeptune.Terminate();
		mDiffuseTextureNeptune.Terminate();
		mPixelShaderNeptune.Terminate();
		mMeshBufferNeptune.Terminate();
		mVertexShaderNeptune.Terminate();
	}

	// Uranus
	{
		mSamplerUranus.Terminate();
		mDiffuseTextureUranus.Terminate();
		mPixelShaderUranus.Terminate();
		mMeshBufferUranus.Terminate();
		mVertexShaderUranus.Terminate();
	}

	// Saturn
	{
		mSamplerSaturn.Terminate();
		mDiffuseTextureSaturn.Terminate();
		mPixelShaderSaturn.Terminate();
		mMeshBufferSaturn.Terminate();
		mVertexShaderSaturn.Terminate();
	}

	// Jupiter
	{
		mSamplerJupiter.Terminate();
		mDiffuseTextureJupiter.Terminate();
		mPixelShaderJupiter.Terminate();
		mMeshBufferJupiter.Terminate();
		mVertexShaderJupiter.Terminate();
	}

	// Mars
	{
		mSamplerMars.Terminate();
		mDiffuseTextureMars.Terminate();
		mPixelShaderMars.Terminate();
		mMeshBufferMars.Terminate();
		mVertexShaderMars.Terminate();
	}

	// Earth
	{
		mSamplerEarth.Terminate();
		mDiffuseTextureEarth.Terminate();
		mPixelShaderEarth.Terminate();
		mMeshBufferEarth.Terminate();
		mVertexShaderEarth.Terminate();
	}

	// Venus
	{
		mSamplerVenus.Terminate();
		mDiffuseTextureVenus.Terminate();
		mPixelShaderVenus.Terminate();
		mMeshBufferVenus.Terminate();
		mVertexShaderVenus.Terminate();
	}

	// Mercury
	{
		mSamplerMercury.Terminate();
		mDiffuseTextureMercury.Terminate();
		mPixelShaderMercury.Terminate();
		mMeshBufferMercury.Terminate();
		mVertexShaderMercury.Terminate();
	}

	// Sun
	{
		mSamplerSun.Terminate();
		mDiffuseTextureSun.Terminate();
		mPixelShaderSun.Terminate();
		mMeshBufferSun.Terminate();
		mVertexShaderSun.Terminate();
	}

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
	
	// Sun
	{
		mVertexShaderSun.Bind();
		mPixelShaderSun.Bind();

		mDiffuseTextureSun.BindPS(0);
		mSamplerSun.BindPS(0);

		mMeshBufferSun.Render();
	}

	// Mercury
	{
		mVertexShaderMercury.Bind();
		mPixelShaderMercury.Bind();

		mDiffuseTextureMercury.BindPS(0);
		mSamplerMercury.BindPS(0);

		mMeshBufferMercury.Render();
	}

	// Venus
	{
		mVertexShaderVenus.Bind();
		mPixelShaderVenus.Bind();

		mDiffuseTextureVenus.BindPS(0);
		mSamplerVenus.BindPS(0);

		mMeshBufferVenus.Render();
	}

	// Earth
	{
		mVertexShaderEarth.Bind();
		mPixelShaderEarth.Bind();

		mDiffuseTextureEarth.BindPS(0);
		mSamplerEarth.BindPS(0);

		mMeshBufferEarth.Render();
	}

	// Mars
	{
		mVertexShaderMars.Bind();
		mPixelShaderMars.Bind();

		mDiffuseTextureMars.BindPS(0);
		mSamplerMars.BindPS(0);

		mMeshBufferMars.Render();
	}

	// Jupiter
	{
		mVertexShaderJupiter.Bind();
		mPixelShaderJupiter.Bind();

		mDiffuseTextureJupiter.BindPS(0);
		mSamplerJupiter.BindPS(0);

		mMeshBufferJupiter.Render();
	}

	// Saturn
	{
		mVertexShaderSaturn.Bind();
		mPixelShaderSaturn.Bind();

		mDiffuseTextureSaturn.BindPS(0);
		mSamplerSaturn.BindPS(0);

		mMeshBufferSaturn.Render();
	}

	// Uranus
	{
		mVertexShaderUranus.Bind();
		mPixelShaderUranus.Bind();

		mDiffuseTextureUranus.BindPS(0);
		mSamplerUranus.BindPS(0);

		mMeshBufferUranus.Render();
	}

	// Neptune
	{
		mVertexShaderNeptune.Bind();
		mPixelShaderNeptune.Bind();

		mDiffuseTextureNeptune.BindPS(0);
		mSamplerNeptune.BindPS(0);

		mMeshBufferNeptune.Render();
	}

	// Pluto
	{
		mVertexShaderPluto.Bind();
		mPixelShaderPluto.Bind();

		mDiffuseTexturePluto.BindPS(0);
		mSamplerPluto.BindPS(0);

		mMeshBufferPluto.Render();
	}

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
			mVertexShaderSun.Bind();
			mPixelShaderSun.Bind();

			mDiffuseTextureSun.BindPS(0);
			mSamplerSun.BindPS(0);

			mMeshBufferSun.Render();
			break;
		
		case 1: // Mercury
			mVertexShaderMercury.Bind();
			mPixelShaderMercury.Bind();

			mDiffuseTextureMercury.BindPS(0);
			mSamplerMercury.BindPS(0);

			mMeshBufferMercury.Render();
			break;

		case 2: // Venus
			mVertexShaderVenus.Bind();
			mPixelShaderVenus.Bind();

			mDiffuseTextureVenus.BindPS(0);
			mSamplerVenus.BindPS(0);

			mMeshBufferVenus.Render();
			break;

		case 3: // Earth
			mVertexShaderEarth.Bind();
			mPixelShaderEarth.Bind();

			mDiffuseTextureEarth.BindPS(0);
			mSamplerEarth.BindPS(0);

			mMeshBufferEarth.Render();
			break;

		case 4: // Mars
			mVertexShaderMars.Bind();
			mPixelShaderMars.Bind();

			mDiffuseTextureMars.BindPS(0);
			mSamplerMars.BindPS(0);

			mMeshBufferMars.Render();
			break;

		case 5: // Jupiter
			mVertexShaderJupiter.Bind();
			mPixelShaderJupiter.Bind();

			mDiffuseTextureJupiter.BindPS(0);
			mSamplerJupiter.BindPS(0);

			mMeshBufferJupiter.Render();
			break;

		case 6: // Saturn
			mVertexShaderSaturn.Bind();
			mPixelShaderSaturn.Bind();

			mDiffuseTextureSaturn.BindPS(0);
			mSamplerSaturn.BindPS(0);

			mMeshBufferSaturn.Render();
			break;

		case 7: // Uranus
			mVertexShaderUranus.Bind();
			mPixelShaderUranus.Bind();

			mDiffuseTextureUranus.BindPS(0);
			mSamplerUranus.BindPS(0);

			mMeshBufferUranus.Render();
			break;

		case 8: // Neptune
			mVertexShaderNeptune.Bind();
			mPixelShaderNeptune.Bind();

			mDiffuseTextureNeptune.BindPS(0);
			mSamplerNeptune.BindPS(0);

			mMeshBufferNeptune.Render();
			break;

		case 9: // Pluto
			mVertexShaderPluto.Bind();
			mPixelShaderPluto.Bind();

			mDiffuseTexturePluto.BindPS(0);
			mSamplerPluto.BindPS(0);

			mMeshBufferPluto.Render();
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
