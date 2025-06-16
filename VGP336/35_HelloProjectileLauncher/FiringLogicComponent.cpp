#include "BulletComponent.h"
#include "FiringLogicComponent.h"
#include <ThanksEngine/Inc/RigidBodyComponent.h>

#include "BulletPoolService.h"

using namespace ThanksEngine;
using namespace ThanksEngine::Graphics;
using namespace ThanksEngine::Math;
using namespace ThanksEngine::Physics;
using namespace ThanksEngine::Input;

void FiringLogicComponent::Update(float deltaTime)
{
	if (InputSystem::Get()->IsMousePressed(MouseButton::LBUTTON))
	{
		if (mTimeSinceLastFire >= mFireRate)
		{
			OnFire();
			mTimeSinceLastFire = 0.0f;
		}
		else
		{
			mTimeSinceLastFire += deltaTime;
		}
	}
	else
	{
		mTimeSinceLastFire += deltaTime;
	}
}

void FiringLogicComponent::Deserialize(const rapidjson::Value& value)
{
	if (value.HasMember("ProjectilePrefabPath"))
	{
		mProjectilePrefabPath = value["ProjectilePrefabPath"].GetString();
	}
	if (value.HasMember("MuzzleVelocity"))
	{
		mMuzzleVelocity = value["MuzzleVelocity"].GetFloat();
	}
	if (value.HasMember("FireRate"))
	{
		mFireRate = value["FireRate"].GetFloat();
	}
}

void FiringLogicComponent::OnFire()
{
	auto bullet = GetOwner().GetWorld().GetService<BulletPoolService>()->GetNextBulletComponent();

	ThanksEngine::Graphics::Camera camera = GetOwner().GetWorld().GetService<CameraService>()->GetMain();
	
	bullet->SetSpawnAndVelocity(camera.GetPosition(), camera.GetDirection() * mMuzzleVelocity);
}