#include <ThanksEngine/Inc/ThanksEngine.h>

class GameState : public ThanksEngine::AppState
{
public:
	void Initialize() override
	{
		LOG("Game State Initialized");
	}
	void Terminate() override
	{
		LOG("Game State Terminated");
	}
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	ThanksEngine::AppConfig config;
	config.appName = L"Hello Window";

	ThanksEngine::App& myApp = ThanksEngine::MainApp();
	myApp.AddState<GameState>("GameState");
	myApp.Run(config);

	return(0);
}