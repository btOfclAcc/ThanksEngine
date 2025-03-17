#pragma once

#include <ThanksEngine/Inc/ThanksEngine.h>

enum character
{
	Maria,
	MariaUnarmed,
	Medea,
	Arissa,
	Pirate
};

class GameState : public ThanksEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Render() override;
	void DebugUI() override;

	void Update(float deltaTime);
protected:
	void UpdateCamera(float deltaTime);

    void IncreamentAnimatorEvent(character c, bool l);
    void OnMoveEvent();
    void XBlastSoundEvent();
	void BlackOutEvent();
	void WhoDecideEvent();
	void RaveEvent();
	void ScratchEvent();
	void CombatEvent();
	void ExitCombatEvent();

    ThanksEngine::Graphics::Camera mCamera;
    ThanksEngine::Graphics::ParticleSystemEffect mParticleSystemEffect;
    ThanksEngine::Physics::ParticleSystem mParticleSystem;

    ThanksEngine::Graphics::RenderObject mDisco;
    ThanksEngine::Graphics::RenderObject mSun;
    ThanksEngine::Graphics::RenderObject mGround;
    ThanksEngine::Graphics::DirectionalLight mDirectionalLight;
    ThanksEngine::Graphics::StandardEffect mStandardEffect;

    // character data
    ThanksEngine::Graphics::RenderGroup mCharacterMaria;
    ThanksEngine::Graphics::Animator mCharacterMariaAnimator;
	int mCharacterMariaAnimatorIndex = -1;

    ThanksEngine::Graphics::RenderGroup mCharacterMariaUnarmed;
    ThanksEngine::Graphics::Animator mCharacterMariaUnarmedAnimator;
    int mCharacterMariaUnarmedAnimatorIndex = 0;

    ThanksEngine::Graphics::RenderGroup mCharacterMedea;
    ThanksEngine::Graphics::Animator mCharacterMedeaAnimator;
    int mCharacterMedeaAnimatorIndex = 0;

    ThanksEngine::Graphics::RenderGroup mCharacterArissa;
    ThanksEngine::Graphics::Animator mCharacterArissaAnimator;
    int mCharacterArissaAnimatorIndex = 0;

    ThanksEngine::Graphics::RenderGroup mCharacterPirate;
    ThanksEngine::Graphics::Animator mCharacterPirateAnimator;
    int mCharacterPirateAnimatorIndex = 0;

	// sound
    ThanksEngine::Math::Vector3 mOffset = { 0.0f, 0.0f, 0.0f };
    ThanksEngine::Audio::SoundId mGunEventId = 0;
    ThanksEngine::Audio::SoundId mXBlastEventId = 0;
    ThanksEngine::Audio::SoundId mExplosionEventId = 0;
	ThanksEngine::Audio::SoundId mBlackOutEventId = 0;
	ThanksEngine::Audio::SoundId mWhoDecideEventId = 0;
	ThanksEngine::Audio::SoundId mRaveEventId = 0;
	ThanksEngine::Audio::SoundId mScratchEventId = 0;
	ThanksEngine::Audio::SoundId mCombatEventId = 0;

	bool mPauseMaria = false;
	bool mPausePirate = false;

    // animation
    ThanksEngine::Graphics::Animation mAnimationDisco;
    float mAnimationTimeDisco = 0.0f;
	ThanksEngine::Graphics::Animation mAnimationSun;
	float mAnimationTimeSun = 0.0f;
    ThanksEngine::Graphics::Animation mAnimationMaria;
	float mAnimationTimeMaria = 0.0f;
    ThanksEngine::Graphics::Animation mAnimationMariaUnarmed;
	float mAnimationTimeMariaUnarmed = 0.0f;
    ThanksEngine::Graphics::Animation mAnimationMedea;
	float mAnimationTimeMedea = 0.0f;
    ThanksEngine::Graphics::Animation mAnimationArissa;
	float mAnimationTimeArissa = 0.0f;
    ThanksEngine::Graphics::Animation mAnimationPirate;
	float mAnimationTimePirate = 0.0f;

    float mTimer = 0;
};