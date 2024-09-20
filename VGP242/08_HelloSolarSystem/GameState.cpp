#include "GameState.h"

#define ToScale TRUE

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
	mTimeRate = 1;

	if (ToScale)
	{
		mCamera.SetPosition({ 0.0f, 100.0f, -300.0f });
	}
	else
	{
		mCamera.SetPosition({ 0.0f, 5.0f, -15.0f });
	}
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mRenderTargetCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mRenderTargetCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	mRenderTargetCamera.SetAspectRatio(1.0f);

	constexpr uint32_t size = 512;
	mRenderTarget.Initialize(size, size, RenderTarget::Format::RGBA_U8);

	mConstantBuffer.Initialize(sizeof(Matrix4));

	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexture.fx";
	mVertexShader.Initialize<VertexPX>(shaderFile);
	mPixelShader.Initialize(shaderFile);

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

	MeshPX mesh;

	// Sun
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 109.0f : 3.0f);
		mSun.mRadius = (ToScale) ? 109.0f : 3.0f;

		mSun.mMeshBuffer.Initialize<MeshPX>(mesh);
		mSun.mDiffuseTexture.Initialize("../../Assets/Images/planets/sun.jpg");

		mSun.mRotationPeriod = -27.0f;
		mSun.mOrbitPeriod = 0.0f;

		mSun.mRotationSpeed = 1 / -27.0f;
		mSun.mTilt = 7.25f / 180.0f * Math::Constants::Pi;
		mSun.mDistanceFromSun = (ToScale) ? 0.0f : 0.0f;
		mSun.mDistanceFromSun /= reducer;
		mSun.mOrbitSpeed = 0.0f;
	}

	// Mercury
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 0.383f : 0.5f);
		mMercury.mRadius = (ToScale) ? 0.383f : 0.5f;

		mMercury.mMeshBuffer.Initialize<MeshPX>(mesh);
		mMercury.mDiffuseTexture.Initialize("../../Assets/Images/planets/mercury.jpg");

		mMercury.mRotationPeriod = -58.6f;
		mMercury.mOrbitPeriod = 87.97f;

		mMercury.mRotationSpeed = 1 / -58.6f;
		mMercury.mTilt = 0.034f / 180.0f * Math::Constants::Pi;
		mMercury.mDistanceFromSun = (ToScale) ? 9089.0f : 10.0f;
		mMercury.mDistanceFromSun /= reducer;
		mMercury.mOrbitSpeed = 1 / 87.97f;
	}

	// Venus
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 0.949f : 1.0f);
		mVenus.mRadius = (ToScale) ? 0.949f : 1.0f;

		mVenus.mMeshBuffer.Initialize<MeshPX>(mesh);
		mVenus.mDiffuseTexture.Initialize("../../Assets/Images/planets/venus.jpg");

		mVenus.mRotationPeriod = 243.0f;
		mVenus.mOrbitPeriod = 224.55f;

		mVenus.mRotationSpeed = 1 / 243.0f;
		mVenus.mTilt = 177.4f / 180.0f * Math::Constants::Pi;
		mVenus.mDistanceFromSun = (ToScale) ? 16989.0f : 15.0f;
		mVenus.mDistanceFromSun /= reducer;
		mVenus.mOrbitSpeed = 1 / 224.55f;
	}

	// Earth
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 1.0f : 1.0f);
		mEarth.mRadius = (ToScale) ? 1.0f : 1.0f;

		mEarth.mMeshBuffer.Initialize<MeshPX>(mesh);
		mEarth.mDiffuseTexture.Initialize("../../Assets/Images/planets/earth/earth.jpg");

		mEarth.mRotationPeriod = -1.0f;
		mEarth.mOrbitPeriod = 365.01f;

		mEarth.mRotationSpeed = 1 / -1.0f;
		mEarth.mTilt = 23.4f / 180.0f * Math::Constants::Pi;
		mEarth.mDistanceFromSun = (ToScale) ? 23483.0f : 20.0f;
		mEarth.mDistanceFromSun /= reducer;
		mEarth.mOrbitSpeed = 1 / 365.01f;
	}

	// Mars
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 0.532f : 0.5f);
		mMars.mRadius = (ToScale) ? 0.532f : 0.5f;

		mMars.mMeshBuffer.Initialize<MeshPX>(mesh);
		mMars.mDiffuseTexture.Initialize("../../Assets/Images/planets/mars.jpg");

		mMars.mRotationPeriod = -1.0f;
		mMars.mOrbitPeriod = 686.98f;

		mMars.mRotationSpeed = 1 / -1.0f;
		mMars.mTilt = 25.2f / 180.0f * Math::Constants::Pi;
		mMars.mDistanceFromSun = (ToScale) ? 35772.0f : 24.0f;
		mMars.mDistanceFromSun /= reducer;
		mMars.mOrbitSpeed = 1 / 686.98f;
	}

	// Jupiter
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 11.21f : 2.0f);
		mJupiter.mRadius = (ToScale) ? 11.21f : 2.0f;

		mJupiter.mMeshBuffer.Initialize<MeshPX>(mesh);
		mJupiter.mDiffuseTexture.Initialize("../../Assets/Images/planets/jupiter.jpg");

		mJupiter.mRotationPeriod = -0.41f;
		mJupiter.mOrbitPeriod = 4332.82f;

		mJupiter.mRotationSpeed = 1 / -0.41f;
		mJupiter.mTilt = 3.1f / 180.0f * Math::Constants::Pi;
		mJupiter.mDistanceFromSun = (ToScale) ? 122174.0f : 40.0f;
		mJupiter.mDistanceFromSun /= reducer;
		mJupiter.mOrbitSpeed = 1 / 4332.82f;
	}

	// Saturn
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 9.45f : 2.0f);
		mSaturn.mRadius = (ToScale) ? 9.45f : 2.0f;

		mSaturn.mMeshBuffer.Initialize<MeshPX>(mesh);
		mSaturn.mDiffuseTexture.Initialize("../../Assets/Images/planets/saturn.jpg");

		mSaturn.mRotationPeriod = -0.45f;
		mSaturn.mOrbitPeriod = 10759.22f;

		mSaturn.mRotationSpeed = 1 / -0.45f;
		mSaturn.mTilt = 26.7f / 180.0f * Math::Constants::Pi;
		mSaturn.mDistanceFromSun = (ToScale) ? 223867.0f : 50.0f;
		mSaturn.mDistanceFromSun /= reducer;
		mSaturn.mOrbitSpeed = 1 / 10759.22f;
	}

	// Uranus
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 4.01f : 1.5f);
		mUranus.mRadius = (ToScale) ? 4.01f : 1.5f;

		mUranus.mMeshBuffer.Initialize<MeshPX>(mesh);
		mUranus.mDiffuseTexture.Initialize("../../Assets/Images/planets/uranus.jpg");

		mUranus.mRotationPeriod = 0.72f;
		mUranus.mOrbitPeriod = 30685.0f;

		mUranus.mRotationSpeed = 1 / 0.72f;
		mUranus.mTilt = 97.8f / 180.0f * Math::Constants::Pi;
		mUranus.mDistanceFromSun = (ToScale) ? 450409.0f : 60.0f;
		mUranus.mDistanceFromSun /= reducer;
		mUranus.mOrbitSpeed = 1 / 30685.0f;
	}

	// Neptune
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 3.88f : 1.5f);
		mNeptune.mRadius = (ToScale) ? 3.88f : 1.5f;

		mNeptune.mMeshBuffer.Initialize<MeshPX>(mesh);
		mNeptune.mDiffuseTexture.Initialize("../../Assets/Images/planets/neptune.jpg");

		mNeptune.mRotationPeriod = -0.67f;
		mNeptune.mOrbitPeriod = 60190.03f;

		mNeptune.mRotationSpeed = 1 / -0.67f;
		mNeptune.mTilt = 28.3f / 180.0f * Math::Constants::Pi;
		mNeptune.mDistanceFromSun = (ToScale) ? 705693.0f : 66.0f;
		mNeptune.mDistanceFromSun /= reducer;
		mNeptune.mOrbitSpeed = 1 / 60190.03f;
	}

	// Pluto
	{
		mesh = MeshBuilder::CreateSpherePX(60, 60, (ToScale) ? 0.186f : 0.25f);
		mPluto.mRadius = (ToScale) ? 0.186f : 0.25f;

		mPluto.mMeshBuffer.Initialize<MeshPX>(mesh);
		mPluto.mDiffuseTexture.Initialize("../../Assets/Images/planets/pluto.jpg");

		mPluto.mRotationPeriod = -6.39f;
		mPluto.mOrbitPeriod = 90560.0f;

		mPluto.mRotationSpeed = 1 / -6.39f;
		mPluto.mTilt = 122.5f / 180.0f * Math::Constants::Pi;
		mPluto.mDistanceFromSun = (ToScale) ? 926610.0f : 72.0f;
		mPluto.mDistanceFromSun /= reducer;
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

	// Sky Sphere
	{
		mesh = MeshBuilder::CreateSkySpherePX(60, 60, mPluto.mDistanceFromSun * 2);

		mSkySphere.mMeshBuffer.Initialize<MeshPX>(mesh);
		mSkySphere.mDiffuseTexture.Initialize("../../Assets/Images/skysphere/space.jpg");
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

	mSampler.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();

	mConstantBuffer.Terminate();
	mRenderTarget.Terminate();
}

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
	mDeltaTime = deltaTime * mTimeRate;
}

void GameState::UpdateCamera(float deltaTime)
{
	auto input = InputSystem::Get();
	const float moveSpeed = (input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f) * deltaTime * (ToScale) ? 10.0f : 1.0f;
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
	mSampler.BindPS(0);

	// Constant Buffer
	Matrix4 matWorld = Matrix4::Identity;
	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	// Sun & Planets & Drawf Planet
	for (auto renderItem : renderItems)
	{
		renderItem->mRotation += Math::Constants::Pi* renderItem->mRotationSpeed* mDeltaTime;
		renderItem->mOrbit += Math::Constants::Pi* renderItem->mOrbitSpeed* mDeltaTime;

		matWorld = Matrix4::Identity;
		matWorld = 
			Matrix4::RotationY(renderItem->mRotation) *
			Matrix4::RotationX(-renderItem->mTilt) *
			Matrix4::Translation({ 0.0f, 0.0f, renderItem->mDistanceFromSun}) * 
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

	// Render Target
	if (mTarget < 1 || mTarget > 9) mTarget = 0;
	mRenderTargetCamera.SetPosition({ 0.0f, 0.0f, -renderItems[mTarget]->mRadius * 2 });
	mRenderTargetCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	matWorld =
		Matrix4::RotationY(renderItems[mTarget]->mRotation) *
		Matrix4::RotationX(-renderItems[mTarget]->mTilt) *
		Matrix4::RotationY(-renderItems[mTarget]->mOrbit);
	matView = mRenderTargetCamera.GetViewMatrix();
	matProj = mRenderTargetCamera.GetProjectionMatrix();
	matFinal = matWorld * matView * matProj;
	wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mRenderTarget.BeginRender();
	if (mTarget == 0)		mSun.Render();
	else if (mTarget == 1)	mMercury.Render();
	else if (mTarget == 2)	mVenus.Render();
	else if (mTarget == 3)	mEarth.Render();
	else if (mTarget == 4)	mMars.Render();
	else if (mTarget == 5)	mJupiter.Render();
	else if (mTarget == 6)	mSaturn.Render();
	else if (mTarget == 7)	mUranus.Render();
	else if (mTarget == 8)	mNeptune.Render();
	else if (mTarget == 9)	mPluto.Render();
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

	ImGui::DragInt("Time Rate (Days Per Second)", &mTimeRate, 0.1f, 0.0f, 100.0f);

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
	
	ImGui::Combo("Target", &mTarget, items, static_cast<int>(std::size(items)));
	
	ImGui::Image(
		mRenderTarget.GetRawData(),
		{ 256, 256 },
		{ 0, 0 },
		{ 1, 1 },
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 });
	ImGui::End();
}
