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

    mParticleSystemEffect.Initialize();
    mParticleSystemEffect.SetCamera(mCamera);

    ParticleSystemInfo info;
    info.textureId = TextureCache::Get()->LoadTexture("sprites/explosion.png");
    int maxParticles = 100;
    info.particlesPerEmit = { 1, 10 };
    info.delay = 1.0f;
    info.lifeTime = FLT_MAX;
    info.timeBetweenEmit = { 0.2f, 0.4f };
    info.spawnAngle = { -30.0f, 30.0f };
    info.spawnSpeed = { 1.0f, 5.0f };
    info.spawnLifeTime = { 0.5f, 0.75f };
    info.spawnDirection = Math::Vector3::YAxis;
    info.spawnPosition = { 0.0f, 3.0f, 0.0f };
    info.startScale = { Math::Vector3::One, Math::Vector3::One };
    info.endScale = { Math::Vector3::One, Math::Vector3::One };
    info.startColor = { Colors::Black, Colors::White };
    info.endColor = { Colors::Black, Colors::White };
    mParticleSystem.Initialize(info);

    mDirectionalLight.direction = Normalize({ 0.0f, -1.0f, 1.0f });
    mDirectionalLight.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
    mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
    mDirectionalLight.specular = { 0.9f, 0.9f, 0.9f, 1.0f };

    std::filesystem::path shaderFile = L"../../Assets/Shaders/Standard.fx";
    mStandardEffect.Initialize(shaderFile);
    mStandardEffect.SetCamera(mCamera);
    mStandardEffect.SetDirectionalLight(mDirectionalLight);

    Mesh ball = MeshBuilder::CreateSphere(60, 60, 0.5f);
    mDisco.meshBuffer.Initialize(ball);
    mDisco.diffuseMapId = TextureCache::Get()->LoadTexture("Images/checker.bmp");

    ball = MeshBuilder::CreateSphere(60, 60, 0.25f);
    mSun.meshBuffer.Initialize(ball);
    mSun.diffuseMapId = TextureCache::Get()->LoadTexture("planets/sun.jpg");

    mCharacterMaria.Initialize(L"../../Assets/Models/Maria/MariaWeapon.model", &mCharacterMariaAnimator);

    ModelCache::Get()->AddAnimation(mCharacterMaria.modelId, L"../../Assets/Models/Maria/DrawSword2.model");
    ModelCache::Get()->AddAnimation(mCharacterMaria.modelId, L"../../Assets/Models/Maria/Slash.model");
    ModelCache::Get()->AddAnimation(mCharacterMaria.modelId, L"../../Assets/Models/Maria/Impact.model");
    ModelCache::Get()->AddAnimation(mCharacterMaria.modelId, L"../../Assets/Models/Maria/Blocking_Entry.model");
    ModelCache::Get()->AddAnimation(mCharacterMaria.modelId, L"../../Assets/Models/Maria/Blocking_Loop.model");
    ModelCache::Get()->AddAnimation(mCharacterMaria.modelId, L"../../Assets/Models/Maria/Blocking_Impact.model");
    ModelCache::Get()->AddAnimation(mCharacterMaria.modelId, L"../../Assets/Models/Maria/Blocking_Loop.model");
    ModelCache::Get()->AddAnimation(mCharacterMaria.modelId, L"../../Assets/Models/Maria/Blocking_Impact.model");
    ModelCache::Get()->AddAnimation(mCharacterMaria.modelId, L"../../Assets/Models/Maria/Blocking_Loop.model");
    ModelCache::Get()->AddAnimation(mCharacterMaria.modelId, L"../../Assets/Models/Maria/Blocking_Exit.model");
    ModelCache::Get()->AddAnimation(mCharacterMaria.modelId, L"../../Assets/Models/Maria/SpellCast.model");
    mCharacterMariaAnimator.Initialize(mCharacterMaria.modelId);

    mCharacterMariaUnarmed.Initialize(L"../../Assets/Models/Maria/Maria.model", &mCharacterMariaUnarmedAnimator);

    ModelCache::Get()->AddAnimation(mCharacterMariaUnarmed.modelId, L"../../Assets/Models/Maria/Laying.model");
    ModelCache::Get()->AddAnimation(mCharacterMariaUnarmed.modelId, L"../../Assets/Models/Maria/SitUp.model");
    ModelCache::Get()->AddAnimation(mCharacterMariaUnarmed.modelId, L"../../Assets/Models/Maria/UnarmedKick.model");
    ModelCache::Get()->AddAnimation(mCharacterMariaUnarmed.modelId, L"../../Assets/Models/Maria/DrawSword1_NoWeapon.model");
    mCharacterMariaUnarmedAnimator.Initialize(mCharacterMariaUnarmed.modelId);

    mCharacterMedea.Initialize(L"../../Assets/Models/Medea/Medea.model", &mCharacterMedeaAnimator);

    ModelCache::Get()->AddAnimation(mCharacterMedea.modelId, L"../../Assets/Models/Medea/Dancing.model");
    ModelCache::Get()->AddAnimation(mCharacterMedea.modelId, L"../../Assets/Models/Medea/LeftTurn.model");
    ModelCache::Get()->AddAnimation(mCharacterMedea.modelId, L"../../Assets/Models/Medea/DodgeBackward.model");
    ModelCache::Get()->AddAnimation(mCharacterMedea.modelId, L"../../Assets/Models/Medea/Idle.model");
    mCharacterMedeaAnimator.Initialize(mCharacterMedea.modelId);

    mCharacterArissa.Initialize(L"../../Assets/Models/Arissa/Arissa.model", &mCharacterArissaAnimator);

    ModelCache::Get()->AddAnimation(mCharacterArissa.modelId, L"../../Assets/Models/Arissa/Dance.model");
    ModelCache::Get()->AddAnimation(mCharacterArissa.modelId, L"../../Assets/Models/Arissa/DodgeBackward.model");
    ModelCache::Get()->AddAnimation(mCharacterArissa.modelId, L"../../Assets/Models/Arissa/FightIdle.model");
    mCharacterArissaAnimator.Initialize(mCharacterArissa.modelId);

    mCharacterPirate.Initialize(L"../../Assets/Models/Pirate/Pirate.model", &mCharacterPirateAnimator);

    ModelCache::Get()->AddAnimation(mCharacterPirate.modelId, L"../../Assets/Models/Pirate/HangingIdle.model");
    ModelCache::Get()->AddAnimation(mCharacterPirate.modelId, L"../../Assets/Models/Pirate/Climb.model");
    ModelCache::Get()->AddAnimation(mCharacterPirate.modelId, L"../../Assets/Models/Pirate/Forward.model");
    ModelCache::Get()->AddAnimation(mCharacterPirate.modelId, L"../../Assets/Models/Pirate/Idle.model");
    ModelCache::Get()->AddAnimation(mCharacterPirate.modelId, L"../../Assets/Models/Pirate/Dodge.model");
    ModelCache::Get()->AddAnimation(mCharacterPirate.modelId, L"../../Assets/Models/Pirate/Idle.model");
    ModelCache::Get()->AddAnimation(mCharacterPirate.modelId, L"../../Assets/Models/Pirate/ShortDodge.model");
    ModelCache::Get()->AddAnimation(mCharacterPirate.modelId, L"../../Assets/Models/Pirate/RightHook.model");
    ModelCache::Get()->AddAnimation(mCharacterPirate.modelId, L"../../Assets/Models/Pirate/Idle.model");
    ModelCache::Get()->AddAnimation(mCharacterPirate.modelId, L"../../Assets/Models/Pirate/RightHook.model");
    ModelCache::Get()->AddAnimation(mCharacterPirate.modelId, L"../../Assets/Models/Pirate/Idle.model");
    ModelCache::Get()->AddAnimation(mCharacterPirate.modelId, L"../../Assets/Models/Pirate/SpellCasting.model");
    ModelCache::Get()->AddAnimation(mCharacterPirate.modelId, L"../../Assets/Models/Pirate/Idle.model");
    ModelCache::Get()->AddAnimation(mCharacterPirate.modelId, L"../../Assets/Models/Pirate/Fall.model");
    mCharacterPirateAnimator.Initialize(mCharacterPirate.modelId);

	mCharacterMariaUnarmedAnimator.PlayAnimation(0, true);
	mCharacterMedeaAnimator.PlayAnimation(0, true);
	mCharacterArissaAnimator.PlayAnimation(0, true);
	mCharacterPirateAnimator.PlayAnimation(0, true);

    Mesh ground = MeshBuilder::CreateGroundPlane(10, 10, 1.0f);
    mGround.meshBuffer.Initialize(ground);
    mGround.diffuseMapId = TextureCache::Get()->LoadTexture("misc/concrete.jpg");
    mGround.material.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
    mGround.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.specular = { 0.9f, 0.9f, 0.9f, 1.0f };
    mGround.material.power = 20.0f;

    mAnimationTimeDisco = 0.0f;
	mAnimationTimeSun = 0.0f;
	mAnimationTimeMaria = 0.0f;
	mAnimationTimeMariaUnarmed = 0.0f;
	mAnimationTimeMedea = 0.0f;
	mAnimationTimeArissa = 0.0f;
	mAnimationTimePirate = 0.0f;

    mAnimationDisco = AnimationBuilder()
        .AddPositionKey({ 0.0f, 3.0f, 0.0f }, 0.0f)
        .AddEventKey(std::bind(&GameState::RaveEvent, this), 0.01f)

        .AddEventKey([&]() { mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f }; }, 5.0f)
        .AddEventKey([&]() { mDirectionalLight.diffuse = { 1.0f, 0.0f, 0.0f, 1.0f }; }, 6.0f)
        .AddEventKey([&]() { mDirectionalLight.diffuse = { 0.0f, 1.0f, 0.0f, 1.0f }; }, 7.0f)
        .AddEventKey([&]() { mDirectionalLight.diffuse = { 0.0f, 0.0f, 1.0f, 1.0f }; }, 8.0f)
        .AddEventKey([&]() { mDirectionalLight.diffuse = { 1.0f, 0.0f, 0.0f, 1.0f }; }, 9.0f)
        .AddEventKey([&]() { mDirectionalLight.diffuse = { 0.0f, 1.0f, 0.0f, 1.0f }; }, 10.0f)
        .AddEventKey([&]() { mDirectionalLight.diffuse = { 0.0f, 0.0f, 1.0f, 1.0f }; }, 11.0f)
        .AddEventKey([&]() { mDirectionalLight.diffuse = { 1.0f, 0.0f, 0.0f, 1.0f }; }, 12.0f)
        .AddEventKey([&]() { mDirectionalLight.diffuse = { 0.0f, 1.0f, 0.0f, 1.0f }; }, 13.0f)
        .AddEventKey([&]() { mDirectionalLight.diffuse = { 0.0f, 0.0f, 1.0f, 1.0f }; }, 14.0f)
        .AddEventKey([&]() { mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f }; }, 15.0f)

        .AddEventKey(std::bind(&GameState::ScratchEvent, this), 16.5f)
        .AddEventKey(std::bind(&GameState::CombatEvent, this), 17.7f)
        .AddEventKey(std::bind(&GameState::ScratchEvent, this), 34.0f)
		.AddEventKey(std::bind(&GameState::ExitCombatEvent, this), 35.2f)

        .AddRotationKey(Quaternion::Identity, 0.0f)
        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 179.0f * Math::Constants::DegToRad), 9.99f)
        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 180.0f * Math::Constants::DegToRad), 10.0f)
        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 359.0f * Math::Constants::DegToRad), 19.99f)
        .AddRotationKey(Quaternion::Identity, 20.0f)

        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 179.0f * Math::Constants::DegToRad), 29.99f)
        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 180.0f * Math::Constants::DegToRad), 30.0f)
        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 359.0f * Math::Constants::DegToRad), 39.99f)
        .AddRotationKey(Quaternion::Identity, 40.0f)

        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 179.0f * Math::Constants::DegToRad), 49.99f)
        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 180.0f * Math::Constants::DegToRad), 50.0f)
        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 359.0f * Math::Constants::DegToRad), 59.99f)
        .AddRotationKey(Quaternion::Identity, 60.0f)

        .Build();

	mAnimationSun = AnimationBuilder()
        .AddPositionKey({ 0.0f, -2.0f, 0.0f }, 0.0f)
        .AddEventKey([&]() { mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f }; }, 0.0f)
        .AddScaleKey({ 1.0f, 1.0f, 1.0f }, 0.0f)

        .AddPositionKey({ 0.0f, -2.0f, 0.0f }, 43.499f)
        .AddPositionKey({ 3.25f, 1.25f, -2.125f }, 43.5f)
        .AddEventKey([&]() { mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f }; }, 43.499f)
        .AddEventKey([&]() { mDirectionalLight.diffuse = { 1.0f, 0.5f, 0.0f, 1.0f }; }, 43.5f)

        .AddScaleKey({ 1.0f, 1.0f, 1.0f }, 55.4f)
        .AddPositionKey({ 3.25f, 1.25f, -2.125f }, 55.4f)

        .AddScaleKey({ 2.0f, 2.0f, 2.0f }, 57.0f)

        .AddEventKey([&]() { mDirectionalLight.diffuse = { 1.0f, 0.5f, 0.0f, 1.0f }; }, 59.998f)
        .AddEventKey([&]() { mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f }; }, 59.999f)
        .AddScaleKey({ 2.0f, 2.0f, 2.0f }, 60.0f)
        .AddPositionKey({ 20.0f, 1.25f, -2.125f }, 60.0f)
		.Build();

    mAnimationMaria = AnimationBuilder()
        .AddPositionKey({ 0.0f, -3.0f, 0.0f }, 0.0f)
        .AddEventKey([&]() { mPauseMaria = false; }, 0.0f)
		.AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 270.0f * Math::Constants::DegToRad), 0.0f)

        .AddPositionKey({ 0.0f, -3.0f, 0.0f }, 22.999f)
        .AddPositionKey({ -1.0f, 0.0f, -2.0f }, 23.0f)
        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Maria, false); }, 23.0f)

        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Maria, false); }, 23.5f)

		.AddPositionKey({ -1.0f, 0.0f, -2.0f }, 27.499f)
		.AddPositionKey({ 2.0f, 0.0f, -2.0f }, 27.5f)
		.AddEventKey([&]() { IncreamentAnimatorEvent(character::Maria, false); }, 27.5f)

		.AddEventKey([&]() { IncreamentAnimatorEvent(character::Maria, false); }, 28.3f)

        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Maria, true); }, 29.0f)

        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Maria, false); }, 31.3f)

        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Maria, true); }, 32.0f)

		.AddEventKey([&]() { IncreamentAnimatorEvent(character::Maria, false); }, 36.5f)

		.AddEventKey([&]() { IncreamentAnimatorEvent(character::Maria, true); }, 37.3f)

        .AddEventKey(std::bind(&GameState::WhoDecideEvent, this), 38.5f)
		.AddEventKey([&]() { IncreamentAnimatorEvent(character::Maria, false); }, 40.0f)

        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Maria, false); }, 43.0f)
        .AddEventKey([&]() { mPauseMaria = false; }, 43.499f)
        .AddEventKey([&]() { mPauseMaria = true; }, 43.5f)

        .AddEventKey([&]() { mPauseMaria = true; }, 59.998f)
        .AddEventKey([&]() { mPauseMaria = false; }, 59.999f)
        .AddPositionKey({ 2.0f, 0.0f, -2.0f }, 60.0f)
        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Maria, true); }, 60.0f)

		.Build();

	mAnimationMariaUnarmed = AnimationBuilder()
        .AddPositionKey({ -1.0f, 0.0f, -2.0f }, 0.0f)
        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 270.0f * Math::Constants::DegToRad), 0.0f)
        
		.AddEventKey([&]() { IncreamentAnimatorEvent(character::MariaUnarmed, false); }, 17.0f)

        .AddEventKey([&]() { IncreamentAnimatorEvent(character::MariaUnarmed, false); }, 20.8f)

		.AddEventKey([&]() { IncreamentAnimatorEvent(character::MariaUnarmed, false); }, 22.5f)
        
        .AddPositionKey({ -1.0f, 0.0f, -2.0f }, 22.999f)
        .AddPositionKey({ -1.0f, -2.0f, -2.0f }, 23.0f)

        .AddPositionKey({ -1.0f, -2.0f, -2.0f }, 60.0f)
        .AddEventKey([&]() { IncreamentAnimatorEvent(character::MariaUnarmed, true); }, 60.0f)

        .Build();
    
	mAnimationMedea = AnimationBuilder()
        .AddPositionKey({ -1.0f, 0.0f, 2.0f }, 0.0f)
        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 0.0f * Math::Constants::DegToRad), 0.0f)
        
        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Medea, false); }, 16.0f)
        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 0.0f * Math::Constants::DegToRad), 16.999f)
        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 270.0f * Math::Constants::DegToRad), 17.0f)
		
        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Medea, false); }, 17.0f)
        
        .AddPositionKey({ -1.0f, 0.0f, 2.0f }, 18.499f)
        .AddPositionKey({ -3.0f, 0.0f, 2.0f }, 18.5f)
        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Medea, true); }, 18.5f)

        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Medea, true); }, 60.0f)

        .Build();

	mAnimationArissa = AnimationBuilder()
        .AddPositionKey({ -2.0f, 0.0f, 0.0f }, 0.0f)
        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 270.0f * Math::Constants::DegToRad), 0.0f)
        
        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Arissa, false); }, 17.0f)
        
        .AddPositionKey({ -2.0f, 0.0f, 0.0f }, 18.499f)
        .AddPositionKey({ -4.0f, 0.0f, 0.0f }, 18.5f)
        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Arissa, true); }, 18.5f)

        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Arissa, true); }, 60.0f)
        
        .Build();

	mAnimationPirate = AnimationBuilder()
        .AddPositionKey({ 5.0f, -2.25f, -2.0f }, 0.0f)
        .AddEventKey([&]() { mPausePirate = false; }, 0.0f)
        .AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 90.0f * Math::Constants::DegToRad), 0.0f)
        
        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Pirate, false); }, 15.0f)
        
        .AddPositionKey({ 5.0f, -2.25f, -2.0f }, 18.899f)
        .AddPositionKey({ 4.0f, 0.0f, -2.0f }, 18.9f)
		.AddEventKey([&]() { IncreamentAnimatorEvent(character::Pirate, false); }, 18.9f)

		.AddPositionKey({ 4.0f, 0.0f, -2.0f }, 19.899f)
		.AddPositionKey({ 1.0f, 0.0f, -2.0f }, 19.9f)
		.AddEventKey([&]() { IncreamentAnimatorEvent(character::Pirate, true); }, 19.9f)

        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Pirate, false); }, 21.0f)

		.AddPositionKey({ 1.0f, 0.0f, -2.0f }, 21.999f)
		.AddPositionKey({ 2.8f, 0.0f, -2.0f }, 22.0f)
		.AddEventKey([&]() { IncreamentAnimatorEvent(character::Pirate, true); }, 22.0f)
        
        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Pirate, false); }, 25.2f)

        .AddPositionKey({ 2.8f, 0.0f, -2.0f }, 27.499f)
        .AddPositionKey({ 5.0f, 0.0f, -2.0f }, 27.5f)
        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Pirate, false); }, 27.5f)
        .AddEventKey(std::bind(&GameState::XBlastSoundEvent, this), 27.7f)

		.AddEventKey([&]() { IncreamentAnimatorEvent(character::Pirate, true); }, 28.5f)

        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Pirate, false); }, 31.0f)
        .AddEventKey(std::bind(&GameState::XBlastSoundEvent, this), 31.2f)

        .AddEventKey([&]() { IncreamentAnimatorEvent(character::Pirate, true); }, 32.0f)

		.AddEventKey([&]() { IncreamentAnimatorEvent(character::Pirate, false); }, 35.0f)
        .AddEventKey(std::bind(&GameState::BlackOutEvent, this), 35.2f)
        
		.AddEventKey([&]() { IncreamentAnimatorEvent(character::Pirate, true); }, 37.0f)

        .AddPositionKey({ 5.0f, 0.0f, -2.0f }, 55.9f)
		.AddEventKey([&]() { IncreamentAnimatorEvent(character::Pirate, false); }, 55.0f)
        .AddEventKey([&]() { mPausePirate = false; }, 55.899f)
        .AddEventKey([&]() { mPausePirate = true; }, 55.9f)

        .AddEventKey([&]() { mPausePirate = false; }, 59.998f)
        .AddEventKey([&]() { mPausePirate = false; }, 59.999f)
        .AddPositionKey({ 20.0f, 0.0f, -2.0f }, 60.0f)
		.AddEventKey([&]() { IncreamentAnimatorEvent(character::Pirate, true); }, 60.0f)

        .Build();

    EventManager* em = EventManager::Get();

    mGunEventId = SoundEffectManager::Get()->Load("photongun1.wav");
    mExplosionEventId = SoundEffectManager::Get()->Load("explosion.wav");
    mXBlastEventId = SoundEffectManager::Get()->Load("megamanx_blast.wav");
	mBlackOutEventId = SoundEffectManager::Get()->Load("BlackOut.wav");
	mWhoDecideEventId = SoundEffectManager::Get()->Load("WhoDecides.wav");
	mRaveEventId = SoundEffectManager::Get()->Load("Rave.wav");
	mScratchEventId = SoundEffectManager::Get()->Load("RecordScratch.wav");
	mCombatEventId = SoundEffectManager::Get()->Load("Kombat.wav");
}

void GameState::Terminate()
{
    mGround.Terminate();
	mCharacterPirate.Terminate();
	mCharacterArissa.Terminate();
	mCharacterMedea.Terminate();
	mCharacterMariaUnarmed.Terminate();
	mCharacterMaria.Terminate();
    mSun.Terminate();
    mDisco.Terminate();
    mStandardEffect.Terminate();
    mParticleSystem.Terminate();
    mParticleSystemEffect.Terminate();
}

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
    mParticleSystem.Update(deltaTime);

    if (mAnimationDisco.GetDuration() > 0.0f)
    {
        float prevTime = mAnimationTimeDisco;
        mAnimationTimeDisco += deltaTime;
        mAnimationDisco.PlayEvent(prevTime, mAnimationTimeDisco);
        while (mAnimationTimeDisco > mAnimationDisco.GetDuration())
        {
            mAnimationTimeDisco -= mAnimationDisco.GetDuration();	// Simple loop
        }
    }

    if (mAnimationSun.GetDuration() > 0.0f)
    {
		float prevTime = mAnimationTimeSun;
		mAnimationTimeSun += deltaTime;
        mAnimationSun.PlayEvent(prevTime, mAnimationTimeSun);
        while (mAnimationTimeSun > mAnimationSun.GetDuration())
        {
            mAnimationTimeSun -= mAnimationSun.GetDuration();	// Simple loop
        }
    }

    if (mAnimationMaria.GetDuration() > 0.0f)
    {
		float prevTime = mAnimationTimeMaria;
		mAnimationTimeMaria += deltaTime;
        mAnimationMaria.PlayEvent(prevTime, mAnimationTimeMaria);
        while (mAnimationTimeMaria > mAnimationMaria.GetDuration())
        {
            mAnimationTimeMaria -= mAnimationMaria.GetDuration();	// Simple loop
        }
    }

    if (mAnimationMariaUnarmed.GetDuration() > 0.0f)
    {
		float prevTime = mAnimationTimeMariaUnarmed;
		mAnimationTimeMariaUnarmed += deltaTime;
        mAnimationMariaUnarmed.PlayEvent(prevTime, mAnimationTimeMariaUnarmed);
        while (mAnimationTimeMariaUnarmed > mAnimationMariaUnarmed.GetDuration())
        {
            mAnimationTimeMariaUnarmed -= mAnimationMariaUnarmed.GetDuration();	// Simple loop
        }
    }

    if (mAnimationMedea.GetDuration() > 0.0f)
    {
		float prevTime = mAnimationTimeMedea;
		mAnimationTimeMedea += deltaTime;
        mAnimationMedea.PlayEvent(prevTime, mAnimationTimeMedea);
        while (mAnimationTimeMedea > mAnimationMedea.GetDuration())
        {
            mAnimationTimeMedea -= mAnimationMedea.GetDuration();	// Simple loop
        }
    }

    if (mAnimationArissa.GetDuration() > 0.0f)
    {
		float prevTime = mAnimationTimeArissa;
		mAnimationTimeArissa += deltaTime;
        mAnimationArissa.PlayEvent(prevTime, mAnimationTimeArissa);
        while (mAnimationTimeArissa > mAnimationArissa.GetDuration())
        {
            mAnimationTimeArissa -= mAnimationArissa.GetDuration();	// Simple loop
        }
    }

    if (mAnimationPirate.GetDuration() > 0.0f)
    {
		float prevTime = mAnimationTimePirate;
		mAnimationTimePirate += deltaTime;
        mAnimationPirate.PlayEvent(prevTime, mAnimationTimePirate);
        while (mAnimationTimePirate > mAnimationPirate.GetDuration())
        {
            mAnimationTimePirate -= mAnimationPirate.GetDuration();	// Simple loop
        }
    }

	if (!mPauseMaria)
	{
		mCharacterMariaAnimator.Update(deltaTime);
	}
	mCharacterMariaUnarmedAnimator.Update(deltaTime);
	mCharacterMedeaAnimator.Update(deltaTime);
    mCharacterArissaAnimator.Update(deltaTime);
    if (!mPausePirate)
    {
        mCharacterPirateAnimator.Update(deltaTime);
    }

    mTimer += deltaTime;
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

void GameState::IncreamentAnimatorEvent(character c, bool l)
{
    switch (c)
    {
    case character::Maria:
		mCharacterMariaAnimatorIndex++;
        if (mCharacterMariaAnimatorIndex >= mCharacterMariaAnimator.GetAnimationCount())
        {
			mCharacterMariaAnimatorIndex = -1;
        }
		mCharacterMariaAnimator.PlayAnimation(mCharacterMariaAnimatorIndex, l);
		break;
	case character::MariaUnarmed:
		mCharacterMariaUnarmedAnimatorIndex++;
        if (mCharacterMariaUnarmedAnimatorIndex >= mCharacterMariaUnarmedAnimator.GetAnimationCount())
        {
			mCharacterMariaUnarmedAnimatorIndex = 0;
        }
		mCharacterMariaUnarmedAnimator.PlayAnimation(mCharacterMariaUnarmedAnimatorIndex, l);
		break;
	case character::Medea:
		mCharacterMedeaAnimatorIndex++;
        if (mCharacterMedeaAnimatorIndex >= mCharacterMedeaAnimator.GetAnimationCount())
        {
            mCharacterMedeaAnimatorIndex = 0;
        }
		mCharacterMedeaAnimator.PlayAnimation(mCharacterMedeaAnimatorIndex, l);
		break;
	case character::Arissa:
		mCharacterArissaAnimatorIndex++;
		if (mCharacterArissaAnimatorIndex >= mCharacterArissaAnimator.GetAnimationCount())
		{
			mCharacterArissaAnimatorIndex = 0;
		}
		mCharacterArissaAnimator.PlayAnimation(mCharacterArissaAnimatorIndex, l);
		break;
	case character::Pirate:
		mCharacterPirateAnimatorIndex++;
        if (mCharacterPirateAnimatorIndex >= mCharacterPirateAnimator.GetAnimationCount())
        {
			mCharacterPirateAnimatorIndex = 0;
        }
		mCharacterPirateAnimator.PlayAnimation(mCharacterPirateAnimatorIndex, l);
		break;
	default:
		ASSERT(false, "HelloAnimatedScene: Invalid Character");
		break;
    }
}

void GameState::OnMoveEvent()
{
    SoundEffectManager::Get()->Play(mExplosionEventId);
}

void GameState::XBlastSoundEvent()
{
    SoundEffectManager::Get()->Play(mXBlastEventId);
}

void GameState::BlackOutEvent()
{
	SoundEffectManager::Get()->Play(mBlackOutEventId);
}

void GameState::WhoDecideEvent()
{
	SoundEffectManager::Get()->Play(mWhoDecideEventId);
}

void GameState::RaveEvent()
{
	SoundEffectManager::Get()->Play(mRaveEventId);
}

void GameState::ScratchEvent()
{
	SoundEffectManager::Get()->Play(mScratchEventId);
}

void GameState::CombatEvent()
{
	SoundEffectManager::Get()->Play(mCombatEventId);
}

void GameState::ExitCombatEvent()
{
	SoundEffectManager::Get()->Stop(mCombatEventId);
}

void GameState::Render()
{
    mStandardEffect.Begin();
        mStandardEffect.Render(mGround);
        mStandardEffect.Render(mDisco);
    mStandardEffect.End();

    mParticleSystemEffect.Begin();
        mParticleSystem.Render(mParticleSystemEffect);
    mParticleSystemEffect.End();

    mDisco.transform = mAnimationDisco.GetTransform(mAnimationTimeDisco);
    mSun.transform = mAnimationSun.GetTransform(mAnimationTimeSun);
	mCharacterMaria.transform = mAnimationMaria.GetTransform(mAnimationTimeMaria);
	mCharacterMariaUnarmed.transform = mAnimationMariaUnarmed.GetTransform(mAnimationTimeMariaUnarmed);
	mCharacterMedea.transform = mAnimationMedea.GetTransform(mAnimationTimeMedea);
	mCharacterArissa.transform = mAnimationArissa.GetTransform(mAnimationTimeArissa);
	mCharacterPirate.transform = mAnimationPirate.GetTransform(mAnimationTimePirate);
    
    mStandardEffect.Begin();
        mStandardEffect.Render(mGround);
        mStandardEffect.Render(mDisco);
        mStandardEffect.Render(mSun);
		mStandardEffect.Render(mCharacterMaria);
		mStandardEffect.Render(mCharacterMariaUnarmed);
		mStandardEffect.Render(mCharacterMedea);
		mStandardEffect.Render(mCharacterArissa);
		mStandardEffect.Render(mCharacterPirate);
    mStandardEffect.End();
}

bool checkBox = true;
bool groundGrid = false;

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
        if (ImGui::CollapsingHeader("Animation", ImGuiTreeNodeFlags_DefaultOpen))
        {
			ImGui::LabelText("Time", "%f", mTimer);
        }
	ImGui::End();

	if (groundGrid)
	{
		SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	}
    SimpleDraw::Render(mCamera);
}