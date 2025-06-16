#include "BulletComponent.h"
#include "CustomParticleComponent.h"
#include "ExplosionComponent.h"
#include <ThanksEngine/Inc/RigidBodyComponent.h>

#include "BulletPoolService.h"

using namespace ThanksEngine;
using namespace ThanksEngine::Graphics;
using namespace ThanksEngine::Math;
using namespace ThanksEngine::Physics;
using namespace ThanksEngine::Input;

void BulletComponent::Initialize()
{
	mInitialPos = GetOwner().GetComponent<TransformComponent>()->position;

	mBulletRigidBodyComponent = GetOwner().GetComponent<RigidBodyComponent>();
	mBulletRigidBodyComponent->ToggleGravity();
	//mBulletRigidBodyComponent->SetDynamicOverride(true);

	//mGroundRigidBodyComponent = GetOwner().GetParent()->GetComponent<RigidBodyComponent>();
	//GetOwner().SetParent(nullptr);

	//mExplosionParticleComponent = GetOwner().GetChild(0)->GetComponent<CustomParticleComponent>();
	//mExplosionParticleComponent->SetSpawnOverride(true);

	mExplosionComponent = GetOwner().GetChild(0)->GetComponent<ExplosionComponent>();

	GetOwner().GetComponent<CustomParticleComponent>()->SetSpawnOverride(true);

	GetOwner().GetWorld().GetService<BulletPoolService>()->Register(this);
}

void BulletComponent::Terminate()
{
	GetOwner().GetWorld().GetService<BulletPoolService>()->Unregister(this);
	//mExplosionParticleComponent = nullptr;
	//mGroundRigidBodyComponent = nullptr;
	mBulletRigidBodyComponent = nullptr;
}

void BulletComponent::Update(float deltaTime)
{
	//mBulletRigidBodyComponent->CheckCollision(mGroundRigidBodyComponent)
	if (!mDeactivated && !mTriggered && GetOwner().GetComponent<TransformComponent>()->position.y <= 0.2)
	{
		OnCollision();
		mTriggered = true;
	}

	if (!mTriggered && !mDeactivated)
	{
		mBulletCurrTime += deltaTime;

		if (mBulletCurrTime >= mBulletLifetime)
		{
			OnCollision();
			mDeactivated = true;
		}
	}
}

void BulletComponent::Deserialize(const rapidjson::Value& value)
{
	if (value.HasMember("BulletLifetime"))
	{
		mBulletLifetime = value["BulletLifetime"].GetFloat();
	}
}

void BulletComponent::SetSpawnAndVelocity(const ThanksEngine::Math::Vector3& spawnPosition, const ThanksEngine::Math::Vector3& spawnVelocity)
{
	mDeactivated = false;
	//mBulletRigidBodyComponent->SetDynamicOverride(false);
	mBulletRigidBodyComponent->ToggleGravity();
	mBulletRigidBodyComponent->SetPosition(spawnPosition);
	mBulletRigidBodyComponent->SetVelocity(spawnVelocity);
	GetOwner().GetComponent<CustomParticleComponent>()->SetSpawnOverride(false);
}

void BulletComponent::OnCollision()
{
	mExplosionComponent->OnCollision();

	GetOwner().GetComponent<CustomParticleComponent>()->SetSpawnOverride(true);

	//mBulletRigidBodyComponent->SetDynamicOverride(true);
	mBulletRigidBodyComponent->SetVelocity(ThanksEngine::Math::Vector3::Zero);
	mBulletRigidBodyComponent->ToggleGravity();
}

void BulletComponent::Reset()
{
	//mBulletRigidBodyComponent->SetDynamicOverride(false);
	mBulletRigidBodyComponent->SetPosition(mInitialPos);
	mBulletRigidBodyComponent->SetVelocity(Math::Vector3::Zero);
	GetOwner().GetComponent<CustomParticleComponent>()->SetSpawnOverride(true);

	mTriggered = false;
	mDeactivated = true;
	mBulletCurrTime = 0.0f;
}