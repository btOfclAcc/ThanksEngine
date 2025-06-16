#pragma once

#include "CustomTypeIds.h"

class CustomParticleComponent;

class ExplosionComponent : public ThanksEngine::Component
{
public:
	SET_TYPE_ID(CustomComponentId::Explosion);

	void Initialize() override;
	void Update(float deltaTime) override;
	void Deserialize(const rapidjson::Value& value) override;

	void OnCollision();

	void Reset();

private:
	float mExplosionDeactivateTime = 1.0f;
	float mExpCurrTime = 0.0f;

	bool mDeactivated = true;
};