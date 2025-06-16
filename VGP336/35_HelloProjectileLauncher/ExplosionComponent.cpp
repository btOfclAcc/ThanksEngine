#include "BulletComponent.h"
#include "CustomParticleComponent.h"
#include "ExplosionComponent.h"

using namespace ThanksEngine;
using namespace ThanksEngine::Graphics;
using namespace ThanksEngine::Math;
using namespace ThanksEngine::Physics;
using namespace ThanksEngine::Input;

void ExplosionComponent::Initialize()
{
	GetOwner().GetComponent<CustomParticleComponent>()->SetActiveOverride(true);
}

void ExplosionComponent::Update(float deltaTime)
{
	GetOwner().GetComponent<TransformComponent>()->position = GetOwner().GetParent()->GetComponent<TransformComponent>()->position;

	if (!mDeactivated)
	{
		mExpCurrTime += deltaTime;

		if (mExpCurrTime >= mExplosionDeactivateTime)
		{
			Reset();
			mDeactivated = true;
		}
	}
}

void ExplosionComponent::Deserialize(const rapidjson::Value& value)
{
	if (value.HasMember("ExplosionDeactivateTime"))
	{
		mExplosionDeactivateTime = value["ExplosionDeactivateTime"].GetFloat();
	}
}

void ExplosionComponent::OnCollision()
{
	GetOwner().GetComponent<CustomParticleComponent>()->SetActiveOverride(false);
	mDeactivated = false;
}

void ExplosionComponent::Reset()
{
	GetOwner().GetComponent<CustomParticleComponent>()->SetActiveOverride(true);
	mExpCurrTime = 0.0f;

	GetOwner().GetParent()->GetComponent<BulletComponent>()->Reset();
}