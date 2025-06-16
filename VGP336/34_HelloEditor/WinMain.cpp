#include <ThanksEngine/Inc/ThanksEngine.h>

#include "GameState.h"
#include "EditTemplateState.h"

using namespace ThanksEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Game World";

	App& myApp = MainApp();
	myApp.AddState<GameState>("GameState");
	myApp.AddState<EditTemplateState>("EditTemplateState");
	myApp.Run(config);
	return(0);
}