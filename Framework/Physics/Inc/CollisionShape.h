#pragma once

namespace ThanksEngine::Physics
{
	class CollisionShape final
	{
	public:
		CollisionShape() = default;
		~CollisionShape();

		void InitializeEmpty();
		void InitializeSphere(float radius);
		void InitializeCapsule(float radius, float height);
		void InitializeBox(const ThanksEngine::Math::Vector3& halfExtents);
		void InitializeHull(const ThanksEngine::Math::Vector3& halfExtents, const ThanksEngine::Math::Vector3& origin);
		void Terminate();

	private:
		friend class RigidBody;
		btCollisionShape* mCollisionShape = nullptr;
	};
}