#include <ThanksEngine/Inc/ThanksEngine.h>

#include "GameState.h"

using namespace ThanksEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Mesh Builder";
	config.winWidth = 1024;
	config.winHeight = 720;

	App& myApp = MainApp();
	myApp.AddState<CubeGameState>("CubeGameState");
	myApp.AddState<RectGameState>("RectGameState");
	myApp.AddState<PlaneGameState>("PlaneGameState");
	myApp.AddState<SphereGameState>("SphereGameState");
	myApp.AddState<CylinderGameState>("CylinderGameState");
	myApp.AddState<SkyBoxGameState>("SkyBoxGameState");
	myApp.AddState<SkySphereGameState>("SkySphereGameState");
	myApp.Run(config);
	return(0);
}