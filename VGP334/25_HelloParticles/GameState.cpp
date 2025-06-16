#include "GameState.h"

using namespace ThanksEngine;
using namespace ThanksEngine::Math;
using namespace ThanksEngine::Graphics;
using namespace ThanksEngine::Core;
using namespace ThanksEngine::Input;
using namespace ThanksEngine::Physics;

void GameState::Initialize()
{
	mGameWorld.AddService<PhysicsService>();
	mCamera.SetPosition({ 0.0f, 2.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 1.0f, 0.0f });

	mParticleSystemEffect.Initialize();
	mParticleSystemEffect.SetCamera(mCamera);

	ParticleSystemInfo info1;
	info1.textureId = TextureCache::Get()->LoadTexture("sprites/explosion.png");
	info1.maxParticles = 200;
	info1.particlesPerEmit = { 200, 200 };
	info1.delay = 1.0f;
	info1.lifeTime = FLT_MAX;
	info1.timeBetweenEmit = { 2.0f, 2.0f };
	info1.spawnAngle = { -180.0f, 180.0f };
	info1.spawnSpeed = { 10.0f, 10.0f };
	info1.spawnLifeTime = { 2.0f, 2.0f };
	info1.spawnDirection = Math::Vector3::YAxis;
	info1.spawnPosition = Math::Vector3::Zero;
	info1.startScale = { Math::Vector3::One, Math::Vector3::One };
	info1.endScale = { Math::Vector3::One, Math::Vector3::One };
	info1.startColor = { Colors::White, Colors::White };
	info1.endColor = { Colors::White, Colors::White };
	info1.particleMass = 0.001f;
	mParticleSystem1.Initialize(info1);

	ParticleSystemInfo info2;
	info2.textureId = TextureCache::Get()->LoadTexture("sprites/explosion.png");
	info2.maxParticles = 100;
	info2.particlesPerEmit = { 1, 4 };
	info2.delay = 1.0f;
	info2.lifeTime = FLT_MAX;
	info2.timeBetweenEmit = { 0.2f, 0.4f };
	info2.spawnAngle = { -30.0f, 30.0f };
	info2.spawnSpeed = { 1.0f, 3.0f };
	info2.spawnLifeTime = { 0.5f, 2.0f };
	info2.spawnDirection = Math::Vector3::YAxis;
	info2.spawnPosition = Math::Vector3::Zero;
	info2.startScale = { Math::Vector3::One, Math::Vector3::One };
	info2.endScale = { Math::Vector3::One, Math::Vector3::One };
	info2.startColor = { Colors::White, Colors::White };
	info2.endColor = { Colors::White, Colors::White };
	mParticleSystem2.Initialize(info2);
}

void GameState::Terminate()
{
	mParticleSystem2.Terminate();
	mParticleSystem1.Terminate();
	mParticleSystemEffect.Terminate();
	mGameWorld.Terminate();
}

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
	mGameWorld.Update(deltaTime);
	mParticleSystem1.Update(deltaTime);
	mParticleSystem2.Update(deltaTime);
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
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed);
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
	if (input->IsKeyPressed(KeyCode::SPACE))
	{
		mParticleSystem1.SetSpawnOverride(mSpawnOverride);
		mSpawnOverride = !mSpawnOverride;
	}
}

void GameState::Render()
{
	mParticleSystemEffect.Begin();
		mParticleSystem1.Render(mParticleSystemEffect);
		mParticleSystem2.Render(mParticleSystemEffect);
	mParticleSystemEffect.End();
}

bool checkBox = true;

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		mParticleSystem1.DebugUI();
		mParticleSystemEffect.DebugUI();
		PhysicsWorld::Get()->DebugUI();
	ImGui::End();

	SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	SimpleDraw::Render(mCamera);
}