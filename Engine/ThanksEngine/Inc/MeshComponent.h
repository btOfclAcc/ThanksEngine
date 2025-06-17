#pragma once

#include "RenderObjectComponent.h"

namespace ThanksEngine
{
    class MeshComponent final : public RenderObjectComponent
    {
    public:
        SET_TYPE_ID(ComponentId::Mesh);

        void Deserialize(const rapidjson::Value& value) override;
        void Serialize(rapidjson::Document& doc, rapidjson::Value& value, const rapidjson::Value& original) override;
        const Graphics::Model& GetModel() const;

    private:
        Graphics::Model mModel;
    };
}