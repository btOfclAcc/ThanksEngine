#pragma once

#include "Component.h"

namespace ThanksEngine
{
	class RigidBodyComponent : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::RigidBody);

		void Initialize() override;
		void Terminate() override;
		void DebugUI() override;
		void Deserialize(const rapidjson::Value& value) override;

		Physics::RigidBody GetRigidBody() const;

		void SetPosition(const Math::Vector3& position);
		void SetVelocity(const Math::Vector3& velocity);
		void SetBounciness(const float bounciness);
		void SetDynamicOverride(bool override);
		void SetGravity(const Math::Vector3& acceleration);
		void SetExchangeAcceleration(const Math::Vector3& acceleration);

		void ToggleGravity();

		bool CheckCollision(const RigidBodyComponent* other) const;

	private:
		friend class PhysicsService;
		Physics::CollisionShape mCollisionShape;
		Physics::RigidBody mRigidBody;
		float mMass = -1.0f;

		Math::Vector3 mOriginalAcceleration = { 0, -9.81f, 0 };
		Math::Vector3 mExchangeAcceleration = Math::Vector3::Zero;
		bool mExchangeAccelerationEnabled = false;
	};
}