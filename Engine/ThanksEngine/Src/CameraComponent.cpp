#include "Precompiled.h"
#include "CameraComponent.h"

using namespace ThanksEngine;
using namespace ThanksEngine::Graphics;
using namespace ThanksEngine::Math;

void CameraComponent::Initialize()
{
}

void CameraComponent::Terminate()
{
}

void CameraComponent::DebugUI()
{
    Vector3 pos = mCamera.GetPosition();
    if (ImGui::DragFloat3("Position##Camera", &pos.x, 0.1f))
    {
        mCamera.SetPosition(pos);
    }
}

Camera& CameraComponent::GetCamera()
{
    return mCamera;
}

const Camera& CameraComponent::GetCamera() const
{
    return mCamera;
}