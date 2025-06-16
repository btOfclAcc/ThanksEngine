#pragma once

#include "CustomTypeIds.h"

class CustomParticleComponent;

class CustomParticleService : public ThanksEngine::Service
{
public:
    SET_TYPE_ID(CustomServiceId::CustomParticleDisplay);

	void Initialize() override;
    void Terminate() override;
    void Render() override;

    void Register(CustomParticleComponent* debugDrawComponent);
    void Unregister(CustomParticleComponent* debugDrawComponent);

private:
    using CustomParticleComponents = std::vector<CustomParticleComponent*>;
    CustomParticleComponents mCustomParticleComponents;

	using ParticleSystems = std::vector<ThanksEngine::Physics::ParticleSystem>;
	ParticleSystems mParticleSystems;

    ThanksEngine::Graphics::ParticleSystemEffect mParticleSystemEffect;
};