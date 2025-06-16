#pragma once

#include <ThanksEngine/Inc/ThanksEngine.h>

enum class CustomComponentId
{
	CustomParticle = static_cast<uint32_t>(ThanksEngine::ComponentId::Count),
	FiringLogic,
	Bullet,
	Explosion
};

enum class CustomServiceId
{
	CustomParticleDisplay = static_cast<uint32_t>(ThanksEngine::ServiceId::Count),
	BulletPool
};