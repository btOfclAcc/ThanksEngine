#pragma once

#include "PhysicsObject.h"

namespace ThanksEngine::Physics
{
	class CollisionShape;

	class RigidBody final : public PhysicsObject
	{
	public:
		RigidBody() = default;
		~RigidBody() override;

		void Initialize(ThanksEngine::Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass = 0.0f, bool addToWorld = true);
		void Terminate();

		void SetPosition(const ThanksEngine::Math::Vector3& position);
		void SetVelocity(const ThanksEngine::Math::Vector3& velocity);
		void SetBounciness(const float bounciness);
		void SetDynamicOverride(bool override);

		void SetGravity(const ThanksEngine::Math::Vector3& acceleration);

		bool CheckCollision(const RigidBody* other) const;

		void Activate();
		void Deactivate();

		bool IsDynamic() const;

	private:
		void SyncWithGraphics() override;
		btRigidBody* GetRigidBody() override;

		btRigidBody* mRigidBody = nullptr;
		btDefaultMotionState* mMotionState = nullptr;
		float mMass = 0.0f;
		bool mDynamicOverride = false;

		ThanksEngine::Graphics::Transform* mGraphicsTransform = nullptr;
	};
}