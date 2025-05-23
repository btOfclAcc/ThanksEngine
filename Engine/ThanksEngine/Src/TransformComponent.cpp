#include "Precompiled.h"
#include "TransformComponent.h"

using namespace ThanksEngine;
using namespace ThanksEngine::Graphics;

void TransformComponent::DebugUI()
{
    ImGui::DragFloat3("Position", &position.x, 0.1f);
    ImGui::DragFloat4("Rotation", &rotation.x, 0.0001f);
    ImGui::DragFloat3("Scale", &scale.x, 0.1f);

    SimpleDraw::AddTransform(GetMatrix4());
}

void TransformComponent::Deserialize(const rapidjson::Value& value)
{
    if (value.HasMember("Position"))
    {
        const auto& pos = value["Position"].GetArray();
        position.x = pos[0].GetFloat();
        position.y = pos[1].GetFloat();
        position.z = pos[2].GetFloat();
    }
    if (value.HasMember("Rotation"))
    {
        const auto& rot = value["Rotation"].GetArray();
        rotation.x = rot[0].GetFloat();
        rotation.y = rot[1].GetFloat();
        rotation.z = rot[2].GetFloat();
        rotation.w = rot[3].GetFloat();
    }
    if (value.HasMember("Scale"))
    {
        const auto& s = value["Scale"].GetArray();
        scale.x = s[0].GetFloat();
        scale.y = s[1].GetFloat();
        scale.z = s[2].GetFloat();
    }
}