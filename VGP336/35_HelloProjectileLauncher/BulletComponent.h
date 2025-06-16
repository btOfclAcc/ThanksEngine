#pragma once

#include "CustomTypeIds.h"

class CustomParticleComponent;
class ExplosionComponent;

class BulletComponent : public ThanksEngine::Component
{
public:
	SET_TYPE_ID(CustomComponentId::Bullet);

	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Deserialize(const rapidjson::Value& value) override;

	void SetSpawnAndVelocity(const ThanksEngine::Math::Vector3& spawnPosition, const ThanksEngine::Math::Vector3& spawnVelocity);

	void OnCollision();

	void Reset();

private:
	ThanksEngine::RigidBodyComponent* mBulletRigidBodyComponent = nullptr;
	//ThanksEngine::RigidBodyComponent* mGroundRigidBodyComponent = nullptr;
	//CustomParticleComponent* mExplosionParticleComponent = nullptr;
	ExplosionComponent* mExplosionComponent = nullptr;

	ThanksEngine::Math::Vector3 mInitialPos = ThanksEngine::Math::Vector3::Zero;

	float mBulletLifetime = 10.0f;
	float mBulletCurrTime = 0.0f;

	bool mTriggered = false;
	bool mDeactivated = true;

	bool mFirst = true;
};