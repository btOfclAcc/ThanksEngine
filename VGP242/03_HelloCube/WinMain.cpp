#include <ThanksEngine/Inc/ThanksEngine.h>

#include "ShapeState.h"

using namespace ThanksEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Cube";
	config.winWidth = 1024;
	config.winHeight = 720;

	App& myApp = MainApp();
	myApp.AddState<ShapeState>("ShapeState");
	myApp.Run(config);
	return(0);
}