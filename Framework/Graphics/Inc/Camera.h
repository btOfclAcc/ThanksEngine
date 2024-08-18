#pragma once

namespace ThanksEngine::Graphics
{
	class Camera
	{
	public:
		enum class ProjectionMode
		{
			Perspective,
			Orphographic
		};

		void SetMode(ProjectionMode mode);

		void SetPosition(const Math::Vector3& position);
		void SetDirection(const Math::Vector3& direction);
		void SetLookAt(const Math::Vector3& target);

		// Perspective Params
		void SetFov(float fov);
		void SetAspectRatio(float ratio);

		// Orthographic Params
		void SetSize(float width, float height);

		void SetNearPlane(float nearPlane);
		void SetFarPlane(float farPlane);

		// Movement Calls

		// Return Values
		const Math::Vector3& GetPosition() const;
		const Math::Vector3& GetDirection() const;

		Math::Matrix4 GetViewMatrix() const;
		Math::Matrix4 GetProjectionMatrix() const;

		// ProjectionMode Transforms
		Math::Matrix4 GetPerspcetiveMatrix() const;
		Math::Matrix4 GetOrthographicMatrix() const;

	private:
		ProjectionMode mProjectionMode = ProjectionMode::Perspective;

		Math::Vector3 mPosition = Math::Vector3::Zero;
		Math::Vector3 mDirection = Math::Vector3::ZAxis;

		float mFov = 60.0f * Math::Constants::DegToRad;
		float mAspectRatio = 0.0f;

		float mWidth = 0.0f;
		float mHeight = 0.0f;

		float mNearPlane = 0.01f;
		float mFarPlane = 10000.0f;
	};
}