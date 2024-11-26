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
	ThanksEngine::Graphics::BillboardEffect mBillBoardEffect;
	ThanksEngine::Graphics::RenderObject mGround;
	ThanksEngine::Graphics::RenderObject mSprite;
};
