#include "Precompiled.h"
#include "TimeUtil.h"

using namespace ThanksEngine;
using namespace ThanksEngine::Core;

float TimeUtil::GetTime()
{
	// gives you the durations since the application started (run time)
	static const auto startTime = std::chrono::high_resolution_clock::now();
	const auto currentTime = std::chrono::high_resolution_clock::now();
	const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
	return milliseconds / 1000.0f;
}

float TimeUtil::GetDeltaTime()
{
	// gives you the durations since last call (run time)
	static auto lastCallTime = std::chrono::high_resolution_clock::now();
	const auto currentTime = std::chrono::high_resolution_clock::now();
	const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastCallTime).count();
	lastCallTime = currentTime;
	return milliseconds / 1000.0f;
}
