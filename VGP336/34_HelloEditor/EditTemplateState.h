#pragma once

#include <ThanksEngine/Inc/ThanksEngine.h>

class EditTemplateState : public ThanksEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Render() override;
	void DebugUI() override;
	void Update(float deltaTime);

protected:
	ThanksEngine::GameWorld mGameWorld;
};
