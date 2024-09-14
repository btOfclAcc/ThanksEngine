#include "GameState.h"

#define ToScale FALSE

#if ToScale
#define reducer 50.0f
#else
#define reducer 1.0f
#endif

using namespace ThanksEngine;
using namespace ThanksEngine::Math;
using namespace ThanksEngine::Graphics;
using namespace ThanksEngine::Core;
using namespace ThanksEngine::Input;

void GameState::Initialize()
{
	mDeltaTime = 0.0f;
	mTime = 0.0f;

	mCamera.SetPosition({ 0.0f, 5.0f, -15.0f });
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
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 109.0f : 3.0f);

		mSun.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mSun.mVertexShader.Initialize<VertexPX>(shaderFile);
		mSun.mPixelShader.Initialize(shaderFile);

		mSun.mDiffuseTexture.Initialize("../../Assets/Images/planets/sun.jpg");
		mSun.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

		mSun.mRotationPeriod = -27.0f;
		mSun.mOrbitPeriod = 0.0f;

		mSun.mRotationSpeed = 1 / -27.0f;
		mSun.mTilt = 7.25f / 180.0f * Math::Constants::Pi;
		mSun.mDistanceFromSun = (ToScale) ? 0.0f : 0.0f;
		mSun.mOrbitSpeed = 0.0f;
	}

	// Mercury
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 0.383f : 0.5f);

		mMercury.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mMercury.mVertexShader.Initialize<VertexPX>(shaderFile);
		mMercury.mPixelShader.Initialize(shaderFile);

		mMercury.mDiffuseTexture.Initialize("../../Assets/Images/planets/mercury.jpg");
		mMercury.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

		mMercury.mRotationPeriod = -58.6f;
		mMercury.mOrbitPeriod = 87.97f;

		mMercury.mRotationSpeed = 1 / -58.6f;
		mMercury.mTilt = 0.034f / 180.0f * Math::Constants::Pi;
		mMercury.mDistanceFromSun = (ToScale) ? 9089.0f : 10.0f;
		mMercury.mOrbitSpeed = 1 / 87.97f;
	}

	// Venus
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 0.949f : 1.0f);

		mVenus.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mVenus.mVertexShader.Initialize<VertexPX>(shaderFile);
		mVenus.mPixelShader.Initialize(shaderFile);

		mVenus.mDiffuseTexture.Initialize("../../Assets/Images/planets/venus.jpg");
		mVenus.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

		mVenus.mRotationPeriod = 243.0f;
		mVenus.mOrbitPeriod = 224.55f;

		mVenus.mRotationSpeed = 1 / 243.0f;
		mVenus.mTilt = 177.4f / 180.0f * Math::Constants::Pi;
		mVenus.mDistanceFromSun = (ToScale) ? 16989.0f : 15.0f;
		mVenus.mOrbitSpeed = 1 / 224.55f;
	}

	// Earth
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 1.0f : 1.0f);

		mEarth.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mEarth.mVertexShader.Initialize<VertexPX>(shaderFile);
		mEarth.mPixelShader.Initialize(shaderFile);

		mEarth.mDiffuseTexture.Initialize("../../Assets/Images/planets/earth/earth.jpg");
		mEarth.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

		mEarth.mRotationPeriod = -1.0f;
		mEarth.mOrbitPeriod = 365.01f;

		mEarth.mRotationSpeed = 1 / -1.0f;
		mEarth.mTilt = 23.4f / 180.0f * Math::Constants::Pi;
		mEarth.mDistanceFromSun = (ToScale) ? 23483.0f : 20.0f;
		mEarth.mOrbitSpeed = 1 / 365.01f;
	}

	// Mars
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 0.532f : 0.5f);

		mMars.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mMars.mVertexShader.Initialize<VertexPX>(shaderFile);
		mMars.mPixelShader.Initialize(shaderFile);

		mMars.mDiffuseTexture.Initialize("../../Assets/Images/planets/mars.jpg");
		mMars.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

		mMars.mRotationPeriod = -1.0f;
		mMars.mOrbitPeriod = 686.98f;

		mMars.mRotationSpeed = 1 / -1.0f;
		mMars.mTilt = 25.2f / 180.0f * Math::Constants::Pi;
		mMars.mDistanceFromSun = (ToScale) ? 35772.0f : 24.0f;
		mMars.mOrbitSpeed = 1 / 686.98f;
	}

	// Jupiter
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 11.21f : 2.0f);

		mJupiter.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mJupiter.mVertexShader.Initialize<VertexPX>(shaderFile);
		mJupiter.mPixelShader.Initialize(shaderFile);

		mJupiter.mDiffuseTexture.Initialize("../../Assets/Images/planets/jupiter.jpg");
		mJupiter.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

		mJupiter.mRotationPeriod = -0.41f;
		mJupiter.mOrbitPeriod = 4332.82f;

		mJupiter.mRotationSpeed = 1 / -0.41f;
		mJupiter.mTilt = 3.1f / 180.0f * Math::Constants::Pi;
		mJupiter.mDistanceFromSun = (ToScale) ? 122174.0f : 40.0f;
		mJupiter.mOrbitSpeed = 1 / 4332.82f;
	}

	// Saturn
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 9.45f : 2.0f);

		mSaturn.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mSaturn.mVertexShader.Initialize<VertexPX>(shaderFile);
		mSaturn.mPixelShader.Initialize(shaderFile);

		mSaturn.mDiffuseTexture.Initialize("../../Assets/Images/planets/saturn.jpg");
		mSaturn.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

		mSaturn.mRotationPeriod = -0.45f;
		mSaturn.mOrbitPeriod = 10759.22f;

		mSaturn.mRotationSpeed = 1 / -0.45f;
		mSaturn.mTilt = 26.7f / 180.0f * Math::Constants::Pi;
		mSaturn.mDistanceFromSun = (ToScale) ? 223867.0f : 50.0f;
		mSaturn.mOrbitSpeed = 1 / 10759.22f;
	}

	// Uranus
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 4.01f : 1.5f);

		mUranus.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mUranus.mVertexShader.Initialize<VertexPX>(shaderFile);
		mUranus.mPixelShader.Initialize(shaderFile);

		mUranus.mDiffuseTexture.Initialize("../../Assets/Images/planets/uranus.jpg");
		mUranus.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

		mUranus.mRotationPeriod = 0.72f;
		mUranus.mOrbitPeriod = 30685.0f;

		mUranus.mRotationSpeed = 1 / 0.72f;
		mUranus.mTilt = 97.8f / 180.0f * Math::Constants::Pi;
		mUranus.mDistanceFromSun = (ToScale) ? 450409.0f : 60.0f;
		mUranus.mOrbitSpeed = 1 / 30685.0f;
	}

	// Neptune
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 3.88f : 1.5f);

		mNeptune.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mNeptune.mVertexShader.Initialize<VertexPX>(shaderFile);
		mNeptune.mPixelShader.Initialize(shaderFile);

		mNeptune.mDiffuseTexture.Initialize("../../Assets/Images/planets/neptune.jpg");
		mNeptune.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

		mNeptune.mRotationPeriod = -0.67f;
		mNeptune.mOrbitPeriod = 60190.03f;

		mNeptune.mRotationSpeed = 1 / -0.67f;
		mNeptune.mTilt = 28.3f / 180.0f * Math::Constants::Pi;
		mNeptune.mDistanceFromSun = (ToScale) ? 705693.0f : 66.0f;
		mNeptune.mOrbitSpeed = 1 / 60190.03f;
	}

	// Pluto
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 0.186f : 0.25f);

		mPluto.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mPluto.mVertexShader.Initialize<VertexPX>(shaderFile);
		mPluto.mPixelShader.Initialize(shaderFile);

		mPluto.mDiffuseTexture.Initialize("../../Assets/Images/planets/pluto.jpg");
		mPluto.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

		mPluto.mRotationPeriod = -6.39f;
		mPluto.mOrbitPeriod = 90560.0f;

		mPluto.mRotationSpeed = 1 / -6.39f;
		mPluto.mTilt = 122.5f / 180.0f * Math::Constants::Pi;
		mPluto.mDistanceFromSun = (ToScale) ? 926610.0f : 72.0f;
		mPluto.mOrbitSpeed = 1 / 90560.0f;
	}

	renderItems.push_back(&mSun);
	renderItems.push_back(&mMercury);
	renderItems.push_back(&mVenus);
	renderItems.push_back(&mEarth);
	renderItems.push_back(&mMars);
	renderItems.push_back(&mJupiter);
	renderItems.push_back(&mSaturn);
	renderItems.push_back(&mUranus);
	renderItems.push_back(&mNeptune);
	renderItems.push_back(&mPluto);

	{
		mesh = MeshBuilder::CreateSkySpherePX(60, 60, mPluto.mDistanceFromSun * 2);

		mSkySphere.mMeshBuffer.Initialize<MeshPX>(mesh);

		shaderFile = L"../../Assets/Shaders/DoTexture.fx";
		mSkySphere.mVertexShader.Initialize<VertexPX>(shaderFile);
		mSkySphere.mPixelShader.Initialize(shaderFile);

		mSkySphere.mDiffuseTexture.Initialize("../../Assets/Images/skysphere/space.jpg");
		mSkySphere.mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	}
}

void GameState::Terminate()
{
	mSkySphere.Terminate();
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
	mDeltaTime = deltaTime;
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

	// Sun & Planets
	for (auto renderItem : renderItems)
	{
		renderItem->mRotation += Math::Constants::Pi* renderItem->mRotationSpeed* mDeltaTime;
		renderItem->mOrbit += Math::Constants::Pi* renderItem->mOrbitSpeed* mDeltaTime;

		matWorld = Matrix4::Identity;
		matWorld = 
			Matrix4::RotationY(renderItem->mRotation) *
			Matrix4::RotationX(renderItem->mTilt) *
			Matrix4::RotationY(-renderItem->mOrbit) * 
			Matrix4::Translation({ 0.0f, 0.0f, renderItem->mDistanceFromSun / reducer}) * 
			Matrix4::RotationY(renderItem->mOrbit);
		matFinal = matWorld * matView * matProj;
		wvp = Transpose(matFinal);
		mConstantBuffer.Update(&wvp);
		mConstantBuffer.BindVS(0);
		renderItem->Render();
	}

	// Sky Sphere
	matWorld = Matrix4::Identity;
	matView = mCamera.GetViewMatrix();
	matProj = mCamera.GetProjectionMatrix();
	matFinal = matWorld * matView * matProj;
	wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);
	mSkySphere.Render();
	
	matWorld = Matrix4::Identity;
	matView = mRenderTargetCamera.GetViewMatrix();
	matProj = mRenderTargetCamera.GetProjectionMatrix();
	matFinal = matWorld * matView * matProj;
	wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mRenderTarget.BeginRender();

	mMercury.mVertexShader.Bind();
	mMercury.mPixelShader.Bind();

	mMercury.mDiffuseTexture.BindPS(0);
	mMercury.mSampler.BindPS(0);

	mMercury.mMeshBuffer.Render();
	/*
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
	*/
	mRenderTarget.EndRender();
}

void GameState::DebugUI()
{
	ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Text("World");

	ImGui::Checkbox("Show Grid", &mShowGrid);
	if (mShowGrid)
	{
		SimpleDraw::AddGroundPlane(500.0f, Colors::White);
	}

	// Sun
	if (ImGui::CollapsingHeader("Sun"))
	{
		ImGui::DragFloat("Rotation Speed", &mSun.mRotationSpeed, 0.01f);
	}

	// Mercury
	if (ImGui::CollapsingHeader("Mercury"))
	{
		ImGui::Checkbox("Show Orbit##Mercury", &mMercury.mShowOrbit);

		ImGui::DragFloat("Rotation Speed##Mercury", &mMercury.mRotationSpeed, 0.01f);
		ImGui::DragFloat("Orbit Speed##Mercury", &mMercury.mOrbitSpeed, 0.01f);
	}
	if (mMercury.mShowOrbit)
	{
		SimpleDraw::AddGroundCircle(60, mMercury.mDistanceFromSun, Colors::White);
	}

	// Venus
	if (ImGui::CollapsingHeader("Venus"))
	{
		ImGui::Checkbox("Show Orbit##Venus", &mVenus.mShowOrbit);

		ImGui::DragFloat("Rotation Speed##Venus", &mVenus.mRotationSpeed, 0.01f);
		ImGui::DragFloat("Orbit Speed##Venus", &mVenus.mOrbitSpeed, 0.01f);
	}
	if (mVenus.mShowOrbit)
	{
		SimpleDraw::AddGroundCircle(60, mVenus.mDistanceFromSun, Colors::White);
	}

	// Earth
	if (ImGui::CollapsingHeader("Earth"))
	{
		ImGui::Checkbox("Show Orbit##Earth", &mEarth.mShowOrbit);

		ImGui::DragFloat("Rotation Speed##Earth", &mEarth.mRotationSpeed, 0.01f);
		ImGui::DragFloat("Orbit Speed##Earth", &mEarth.mOrbitSpeed, 0.01f);
	}
	if (mEarth.mShowOrbit)
	{
		SimpleDraw::AddGroundCircle(60, mEarth.mDistanceFromSun, Colors::White);
	}

	// Mars
	if (ImGui::CollapsingHeader("Mars"))
	{
		ImGui::Checkbox("Show Orbit##Mars", &mMars.mShowOrbit);

		ImGui::DragFloat("Rotation Speed##Mars", &mMars.mRotationSpeed, 0.01f);
		ImGui::DragFloat("Orbit Speed##Mars", &mMars.mOrbitSpeed, 0.01f);
	}
	if (mMars.mShowOrbit)
	{
		SimpleDraw::AddGroundCircle(60, mMars.mDistanceFromSun, Colors::White);
	}

	// Jupiter
	if (ImGui::CollapsingHeader("Jupiter"))
	{
		ImGui::Checkbox("Show Orbit##Jupiter", &mJupiter.mShowOrbit);

		ImGui::DragFloat("Rotation Speed##Jupiter", &mJupiter.mRotationSpeed, 0.01f);
		ImGui::DragFloat("Orbit Speed##Jupiter", &mJupiter.mOrbitSpeed, 0.01f);
	}
	if (mJupiter.mShowOrbit)
	{
		SimpleDraw::AddGroundCircle(60, mJupiter.mDistanceFromSun, Colors::White);
	}

	// Saturn
	if (ImGui::CollapsingHeader("Saturn"))
	{
		ImGui::Checkbox("Show Orbit##Saturn", &mSaturn.mShowOrbit);

		ImGui::DragFloat("Rotation Speed##Saturn", &mSaturn.mRotationSpeed, 0.01f);
		ImGui::DragFloat("Orbit Speed##Saturn", &mSaturn.mOrbitSpeed, 0.01f);
	}
	if (mSaturn.mShowOrbit)
	{
		SimpleDraw::AddGroundCircle(60, mSaturn.mDistanceFromSun, Colors::White);
	}

	// Uranus
	if (ImGui::CollapsingHeader("Uranus"))
	{
		ImGui::Checkbox("Show Orbit##Uranus", &mUranus.mShowOrbit);

		ImGui::DragFloat("Rotation Speed##Uranus", &mUranus.mRotationSpeed, 0.01f);
		ImGui::DragFloat("Orbit Speed##Uranus", &mUranus.mOrbitSpeed, 0.01f);
	}
	if (mUranus.mShowOrbit)
	{
		SimpleDraw::AddGroundCircle(60, mUranus.mDistanceFromSun, Colors::White);
	}

	// Neptune
	if (ImGui::CollapsingHeader("Neptune"))
	{
		ImGui::Checkbox("Show Orbit##Neptune", &mNeptune.mShowOrbit);

		ImGui::DragFloat("Rotation Speed##Neptune", &mNeptune.mRotationSpeed, 0.01f);
		ImGui::DragFloat("Orbit Speed##Neptune", &mNeptune.mOrbitSpeed, 0.01f);
	}
	if (mNeptune.mShowOrbit)
	{
		SimpleDraw::AddGroundCircle(60, mNeptune.mDistanceFromSun, Colors::White);
	}

	// Pluto
	if (ImGui::CollapsingHeader("Pluto"))
	{
		ImGui::Checkbox("Show Orbit##Pluto", &mPluto.mShowOrbit);

		ImGui::DragFloat("Rotation Speed##Pluto", &mPluto.mRotationSpeed, 0.01f);
		ImGui::DragFloat("Orbit Speed##Pluto", &mPluto.mOrbitSpeed, 0.01f);
	}
	if (mPluto.mShowOrbit)
	{
		SimpleDraw::AddGroundCircle(60, mPluto.mDistanceFromSun, Colors::White);
	}

	SimpleDraw::Render(mCamera);
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
