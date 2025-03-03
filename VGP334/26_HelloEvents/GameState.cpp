#include "GameState.h"

using namespace ThanksEngine;
using namespace ThanksEngine::Math;
using namespace ThanksEngine::Graphics;
using namespace ThanksEngine::Core;
using namespace ThanksEngine::Input;
using namespace ThanksEngine::Physics;
using namespace ThanksEngine::Audio;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 2.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 1.0f, 0.0f });

    mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });
    mDirectionalLight.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
    mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
    mDirectionalLight.specular = { 0.9f, 0.9f, 0.9f, 1.0f };

    Mesh mesh = MeshBuilder::CreateSphere(300, 300, 1.0f);

    std::filesystem::path shaderFile = L"../../Assets/Shaders/Standard.fx";
    mStandardEffect.Initialize(shaderFile);
    mStandardEffect.SetCamera(mCamera);
    mStandardEffect.SetDirectionalLight(mDirectionalLight);

    Mesh ball = MeshBuilder::CreateSphere(60, 60, 0.5f);
    mBall.meshBuffer.Initialize(ball);
    mBall.diffuseMapId = TextureCache::Get()->LoadTexture("misc/basketball.jpg");

    Mesh ground = MeshBuilder::CreateGroundPlane(10, 10, 1.0f);
    mGround.meshBuffer.Initialize(ground);
    mGround.diffuseMapId = TextureCache::Get()->LoadTexture("misc/concrete.jpg");

    mAnimationTime = 0.0f;

    mAnimation = AnimationBuilder()
        .AddPositionKey({ 0.0f, 0.5f, 0.0f }, 0.0f)
        .AddPositionKey({ 1.0f, 2.5f, -1.0f }, 0.5f)
        .AddPositionKey({ 0.0f, 0.5f, 0.0f }, 1.0f)

        .AddPositionKey({ -1.0f, 2.5f, -1.0f }, 1.5f)
        .AddPositionKey({ 0.0f, 0.5f, 0.0f }, 2.0f)

        .AddScaleKey({ 1.0f, 0.9f, 1.0f }, 0.0f)
        .AddScaleKey({ 0.9f, 1.1f, 0.9f }, 0.05f)
        .AddScaleKey({ 0.9f, 1.1f, 0.9f }, 0.45f)
        .AddScaleKey({ 1.0f, 1.0f, 1.0f }, 0.5f)
        .AddScaleKey({ 1.0f, 1.0f, 1.0f }, 0.95f)
        .AddScaleKey({ 1.0f, 0.9f, 1.0f }, 1.0f)

        .AddScaleKey({ 0.9f, 1.1f, 0.9f }, 1.05f)
        .AddScaleKey({ 0.9f, 1.1f, 0.9f }, 1.45f)
        .AddScaleKey({ 1.0f, 1.0f, 1.0f }, 1.5f)
        .AddScaleKey({ 1.0f, 1.0f, 1.0f }, 1.95f)
        .AddScaleKey({ 1.0f, 0.9f, 1.0f }, 2.0f)

        .AddRotationKey(Quaternion::Identity, 0.5f)
        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, 180.0f * Math::Constants::DegToRad), 0.5f)
        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, 270.0f * Math::Constants::DegToRad), 0.75f)
        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, 359.0f * Math::Constants::DegToRad), 1.0f)
        .AddRotationKey(Quaternion::Identity, 1.0f)

        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, 180.0f * Math::Constants::DegToRad), 1.5f)
        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, 270.0f * Math::Constants::DegToRad), 1.75f)
        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, 359.0f * Math::Constants::DegToRad), 2.0f)
        .AddRotationKey(Quaternion::Identity, 2.0f)

        .AddEventKey(std::bind(&GameState::XBlastSoundEvent, this), 1.0f)
        .AddEventKey(std::bind(&GameState::OnMoveEvent, this), 2.0f)
        .Build();

    EventManager* em = EventManager::Get();
    mSpacePressedEventId = em->AddListener(EventType::SpacePressed, std::bind(&GameState::OnSpacePressedEvent, this, std::placeholders::_1));
    mFKeyPressedEventId = em->AddListener(EventType::FKeyPressed, std::bind(&GameState::OnFKeyPressedEvent, this, std::placeholders::_1));

    mGunEventId = SoundEffectManager::Get()->Load("photongun1.wav");
    mExplosionEventId = SoundEffectManager::Get()->Load("explosion.wav");
    mXBlastEventId = SoundEffectManager::Get()->Load("megamanx_blast.wav");
    mHurtEventId = SoundEffectManager::Get()->Load("hurt.wav");
}

void GameState::Terminate()
{
    EventManager::Get()->RemoveListener(EventType::SpacePressed, mSpacePressedEventId);
    EventManager::Get()->RemoveListener(EventType::FKeyPressed, mHurtEventId);
    mGround.Terminate();
    mBall.Terminate();
    mStandardEffect.Terminate();
}

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);

    if (mAnimation.GetDuration() > 0.0f)
    {
        float prevTime = mAnimationTime;
        mAnimationTime += deltaTime;
        mAnimation.PlayEvent(prevTime, mAnimationTime);
        while (mAnimationTime > mAnimation.GetDuration())
        {
            mAnimationTime -= mAnimation.GetDuration();	// Simple loop
        }
    }

    if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
    {
        SpacePressedEvent spe;
        EventManager::Broadcast(spe);
    }

    if (InputSystem::Get()->IsKeyPressed(KeyCode::F))
    {
        FKeyPressedEvent fkpe;
        EventManager::Broadcast(fkpe);
    }
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
}

void GameState::OnMoveEvent()
{
    mOffset.x += 0.5f;
    SoundEffectManager::Get()->Play(mExplosionEventId);
}

void GameState::OnSpacePressedEvent(const ThanksEngine::Event& e) const
{
    SoundEffectManager::Get()->Play(mGunEventId);
}

void GameState::OnFKeyPressedEvent(const ThanksEngine::Event& e) const
{
    SoundEffectManager::Get()->Play(mHurtEventId);
}

void GameState::XBlastSoundEvent()
{
    SoundEffectManager::Get()->Play(mXBlastEventId);
}


void GameState::Render()
{
    mBall.transform = mAnimation.GetTransform(mAnimationTime);
    mBall.transform.position += mOffset;
    mStandardEffect.Begin();
        mStandardEffect.Render(mGround);
        mStandardEffect.Render(mBall);
    mStandardEffect.End();
}

bool checkBox = true;

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
        {
            if (ImGui::DragFloat3("Direction", &mDirectionalLight.direction.x, 0.01f))
            {
                mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
            }

            ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
            ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
            ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
        }
	ImGui::End();
}