#include "Precompiled.h"
#include "ThanksEngine.h"

ThanksEngine::App& ThanksEngine::MainApp()
{
	static ThanksEngine::App sApp;
	return sApp;
}