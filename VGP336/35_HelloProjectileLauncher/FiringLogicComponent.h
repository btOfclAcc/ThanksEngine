#pragma once

#include "CustomTypeIds.h"

class FiringLogicComponent : public ThanksEngine::Component
{
public:
	SET_TYPE_ID(CustomComponentId::FiringLogic);

	void Update(float deltaTime) override;
	void Deserialize(const rapidjson::Value& value) override;

	void OnFire();

private:
	std::string mProjectilePrefabPath = "../../Assets/Templates/projectile.json";
	float mMuzzleVelocity = 10.0f;
	float mFireRate = 0.5f;

	float mTimeSinceLastFire = 0.0f;
};