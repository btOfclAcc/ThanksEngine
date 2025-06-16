#include "CustomParticleService.h"
#include "CustomParticleComponent.h"

using namespace ThanksEngine;
using namespace ThanksEngine::Graphics;

void CustomParticleService::Initialize()
{
	mParticleSystemEffect.Initialize();
}

void CustomParticleService::Terminate()
{
	mParticleSystemEffect.Terminate();
}

void CustomParticleService::Render()
{
    mParticleSystemEffect.SetCamera(GetWorld().GetService<CameraService>()->GetMain());
    mParticleSystemEffect.Begin();
    for (CustomParticleComponent* component : mCustomParticleComponents)
    {
        component->mParticleSystem.Render(mParticleSystemEffect);
    }
    mParticleSystemEffect.End();
}

void CustomParticleService::Register(CustomParticleComponent* debugDrawComponent)
{
    auto iter = std::find(mCustomParticleComponents.begin(),
        mCustomParticleComponents.end(), debugDrawComponent);
    if (iter == mCustomParticleComponents.end())
    {
        mCustomParticleComponents.push_back(debugDrawComponent);
    }
}

void CustomParticleService::Unregister(CustomParticleComponent* debugDrawComponent)
{
    auto iter = std::find(mCustomParticleComponents.begin(),
        mCustomParticleComponents.end(), debugDrawComponent);
    if (iter != mCustomParticleComponents.end())
    {
        mCustomParticleComponents.erase(iter);
    }
}