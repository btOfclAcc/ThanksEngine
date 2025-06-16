#pragma once

#include <ThanksEngine/Inc/ThanksEngine.h>

enum class CustomComponentId
{
	CustomDebugDraw = static_cast<uint32_t>(ThanksEngine::ComponentId::Count),
	NewComponent,
	NewComponent2
};

enum class CustomServiceId
{
	CustomDebugDrawDisplay = static_cast<uint32_t>(ThanksEngine::ServiceId::Count),
};