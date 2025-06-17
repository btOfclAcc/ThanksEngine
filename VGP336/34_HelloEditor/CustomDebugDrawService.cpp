#include "CustomDebugDrawService.h"
#include "CustomDebugDrawComponent.h"

using namespace ThanksEngine;
using namespace ThanksEngine::Graphics;

void CustomDebugDrawService::Render()
{
    for (const CustomDebugDrawComponent* component : mCustomDebugDrawComponents)
    {
        component->AddDebugDraw();
    }
}

void CustomDebugDrawService::Register(const CustomDebugDrawComponent* debugDrawComponent)
{
    auto iter = std::find(mCustomDebugDrawComponents.begin(),
        mCustomDebugDrawComponents.end(), debugDrawComponent);
    if (iter == mCustomDebugDrawComponents.end())
    {
        mCustomDebugDrawComponents.push_back(debugDrawComponent);
    }
}

void CustomDebugDrawService::Unregister(const CustomDebugDrawComponent* debugDrawComponent)
{
    auto iter = std::find(mCustomDebugDrawComponents.begin(),
        mCustomDebugDrawComponents.end(), debugDrawComponent);
    if (iter != mCustomDebugDrawComponents.end())
    {
        mCustomDebugDrawComponents.erase(iter);
    }
}