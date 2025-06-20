#pragma once

#include <ThanksEngine/Inc/ThanksEngine.h>


class GameState : public ThanksEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Render() override;
	void DebugUI() override;

	void Update(float deltaTime);
protected:
	void UpdateCamera(float deltaTime);

	ThanksEngine::Graphics::Camera mCamera;
	ThanksEngine::Graphics::DirectionalLight mDirectionalLight;
	ThanksEngine::Graphics::StandardEffect mStandardEffect;

	// ball info
	ThanksEngine::Graphics::RenderObject mBall;
	ThanksEngine::Physics::CollisionShape mBallShape;
	ThanksEngine::Physics::RigidBody mBallRB;

	// ground info
	ThanksEngine::Graphics::RenderObject mGround;
	ThanksEngine::Physics::CollisionShape mGroundShape;
	ThanksEngine::Physics::RigidBody mGroundRB;

	// cloth info
	ThanksEngine::Graphics::RenderObject mCloth;
	ThanksEngine::Graphics::Mesh mClothMesh;
	ThanksEngine::Physics::SoftBody mClothSoftBody;

	ThanksEngine::GameWorld mGameWorld;
};