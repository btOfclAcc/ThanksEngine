#pragma once

#include <ThanksEngine/Inc/ThanksEngine.h>


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

    void OnMoveEvent();
    void OnSpacePressedEvent(const ThanksEngine::Event& e) const;
    void OnFKeyPressedEvent(const ThanksEngine::Event& e) const;
    void XBlastSoundEvent();

    ThanksEngine::Graphics::Camera mCamera;
    ThanksEngine::Graphics::RenderObject mBall;
    ThanksEngine::Graphics::RenderObject mGround;
    ThanksEngine::Graphics::DirectionalLight mDirectionalLight;
    ThanksEngine::Graphics::StandardEffect mStandardEffect;

    ThanksEngine::Math::Vector3 mOffset = { 0.0f, 0.0f, 0.0f };
    ThanksEngine::ListenerId mSpacePressedEventId = 0;
    ThanksEngine::ListenerId mFKeyPressedEventId = 0;
    ThanksEngine::Audio::SoundId mGunEventId = 0;
    ThanksEngine::Audio::SoundId mXBlastEventId = 0;
    ThanksEngine::Audio::SoundId mExplosionEventId = 0;
    ThanksEngine::Audio::SoundId mHurtEventId = 0;

    // animation
    ThanksEngine::Graphics::Animation mAnimation;
    float mAnimationTime = 0.0f;
};