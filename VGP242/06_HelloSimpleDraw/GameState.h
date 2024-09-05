#pragma once

#include <ThanksEngine/Inc/ThanksEngine.h>

enum class DebugDrawType
{
	None,
	Line,
	Sphere,
	AABB,
	FilledAABB,
	GroundCircle,
};

class GameState : public ThanksEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

protected:
	void UpdateCamera(float deltaTime);

	ThanksEngine::Graphics::Camera mCamera;
	DebugDrawType mDebugDrawType = DebugDrawType::None;
};