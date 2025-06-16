#pragma once

#include "CustomTypeIds.h"

class CustomParticleComponent : public ThanksEngine::Component
{
public:
	SET_TYPE_ID(CustomComponentId::CustomParticle);

	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Deserialize(const rapidjson::Value& value) override;

	void SetSpawnOverride(bool override);
	void SetActiveOverride(bool override);

	ThanksEngine::Physics::ParticleSystem mParticleSystem;

private:
	const ThanksEngine::TransformComponent* mTransformComponent = nullptr;
	ThanksEngine::Math::Vector3 mPosition = ThanksEngine::Math::Vector3::Zero;
	ThanksEngine::Color mColor = ThanksEngine::Colors::White;

	uint32_t mSlices = 0;
	uint32_t mRings = 0;
	float mRadius = 0.0f;

	std::string mTextureFile = "sprites/explosion.png";
	int mMaxParticles = 100;
	ThanksEngine::Math::RangeInt mParticlesPerEmit = { 1, 4 };
	float mDelay = 1.0f;
	float mLifeTime = FLT_MAX;
	ThanksEngine::Math::Range<float> mTimeBetweenEmit = { 0.2f, 0.4f };
	ThanksEngine::Math::Range<float> mSpawnAngle = { -30.0f, 30.0f };
	ThanksEngine::Math::Range<float> mSpawnSpeed = { 1.0f, 3.0f };
	ThanksEngine::Math::Range<float> mSpawnLifeTime = { 0.5f, 2.0f };
	ThanksEngine::Math::Vector3 mSpawnDirection = ThanksEngine::Math::Vector3::YAxis;
	ThanksEngine::Math::Vector3 mSpawnPosition = ThanksEngine::Math::Vector3::Zero;
	ThanksEngine::Math::Range<ThanksEngine::Math::Vector3> mStartScale = { ThanksEngine::Math::Vector3::One, ThanksEngine::Math::Vector3::One };
	ThanksEngine::Math::Range<ThanksEngine::Math::Vector3> mEndScale = { ThanksEngine::Math::Vector3::One, ThanksEngine::Math::Vector3::One };
	ThanksEngine::Math::Range<ThanksEngine::Color> mStartColor = { ThanksEngine::Colors::White, ThanksEngine::Colors::White };
	ThanksEngine::Math::Range<ThanksEngine::Color> mEndColor = { ThanksEngine::Colors::White, ThanksEngine::Colors::White };
	float mParticleMass = 1.0f;
};