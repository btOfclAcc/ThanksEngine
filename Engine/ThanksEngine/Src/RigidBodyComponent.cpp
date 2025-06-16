#include "Precompiled.h"
#include "RigidBodyComponent.h"

#include "GameWorld.h"
#include "PhysicsService.h"
#include "TransformComponent.h"

using namespace ThanksEngine;

void RigidBodyComponent::Initialize()
{
	PhysicsService* ps = GetOwner().GetWorld().GetService<PhysicsService>();
	if (ps != nullptr)
	{
		TransformComponent* transformComponent = GetOwner().GetComponent<TransformComponent>();
		mRigidBody.Initialize(*transformComponent, mCollisionShape, mMass, false);
		ps->Register(this);
	}
}

void RigidBodyComponent::Terminate()
{
	PhysicsService* ps = GetOwner().GetWorld().GetService<PhysicsService>();
	if (ps != nullptr)
	{
		ps->Unregister(this);
	}

	mRigidBody.Terminate();
	mCollisionShape.Terminate();
}

void RigidBodyComponent::DebugUI()
{

}

void RigidBodyComponent::Deserialize(const rapidjson::Value& value)
{
	if (value.HasMember("Mass"))
	{
		mMass = value["Mass"].GetFloat();
	}
	if (value.HasMember("ColliderData"))
	{
		mCollisionShape.Terminate();
		auto colliderData = value["ColliderData"].GetObj();
		if (colliderData.HasMember("Shape"))
		{
			std::string shape = colliderData["Shape"].GetString();
			if (shape == "Empty")
			{
				mCollisionShape.InitializeEmpty();
			}
			else if (shape == "Box")
			{
				const auto halfExtents = colliderData["HalfExtents"].GetArray();
				const float x = halfExtents[0].GetFloat();
				const float y = halfExtents[1].GetFloat();
				const float z = halfExtents[2].GetFloat();
				mCollisionShape.InitializeBox({ x, y, z });
			}
			else if (shape == "Sphere")
			{
				const float radius = colliderData["Radius"].GetFloat();
				mCollisionShape.InitializeSphere(radius);
			}
			else if (shape == "Hull")
			{
				const auto halfExtents = colliderData["HalfExtents"].GetArray();
				const float hx = halfExtents[0].GetFloat();
				const float hy = halfExtents[1].GetFloat();
				const float hz = halfExtents[2].GetFloat();
				const auto origin = colliderData["Origin"].GetArray();
				const float ox = origin[0].GetFloat();
				const float oy = origin[1].GetFloat();
				const float oz = origin[2].GetFloat();
				mCollisionShape.InitializeHull({ hx, hy, hz }, { ox, oy, oz });
			}
			else
			{
				ASSERT(false, "RigidBodyComponent: invalid shape type %s", shape.c_str());
			}
		}
		else
		{
			ASSERT(false, "RigidBodyComponent: requires shape data");
		}
	}
	if (value.HasMember("Bounciness"))
	{
		mRigidBody.SetBounciness(value["Bounciness"].GetFloat());
	}
}

Physics::RigidBody RigidBodyComponent::GetRigidBody() const
{
	return mRigidBody;
}

void RigidBodyComponent::SetPosition(const Math::Vector3& position)
{
	mRigidBody.SetPosition(position);
}

void RigidBodyComponent::SetVelocity(const Math::Vector3& velocity)
{
	mRigidBody.SetVelocity(velocity);
}

void RigidBodyComponent::SetBounciness(const float bounciness)
{
	mRigidBody.SetBounciness(bounciness);
}

void RigidBodyComponent::SetDynamicOverride(bool override)
{
	mRigidBody.SetDynamicOverride(override);
}

void RigidBodyComponent::SetGravity(const Math::Vector3& acceleration)
{
	mRigidBody.SetGravity(acceleration);
}

void RigidBodyComponent::SetExchangeAcceleration(const Math::Vector3& acceleration)
{
	mExchangeAcceleration = acceleration;
}

void RigidBodyComponent::ToggleGravity()
{
	if (mExchangeAccelerationEnabled)
	{
		mRigidBody.SetGravity(mOriginalAcceleration);
	}
	else
	{
		mRigidBody.SetGravity(mExchangeAcceleration);
	}
	mExchangeAccelerationEnabled = !mExchangeAccelerationEnabled;
}

bool RigidBodyComponent::CheckCollision(const RigidBodyComponent* other) const
{
	ASSERT(other != nullptr, "RigidBodyComponent: other must not be null");
	return mRigidBody.CheckCollision(&other->mRigidBody);
}
