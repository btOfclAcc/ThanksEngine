#include <ThanksEngine/Inc/ThanksEngine.h>

#include "ShapeState.h"

using namespace ThanksEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Shapes";
	config.winWidth = 800;
	config.winHeight = 800;

	App& myApp = MainApp();
	myApp.AddState<TriangleShapeState>("TriangleShapeState");
	myApp.AddState<DiamondShapeState>("DiamondShapeState");
	myApp.AddState<HeartShapeState>("HeartShapeState");
	myApp.Run(config);
	return(0);
}