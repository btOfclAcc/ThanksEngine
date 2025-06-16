#pragma once

#include "CustomTypeIds.h"

class CustomDebugDrawComponent : public ThanksEngine::Component
{
public:
	SET_TYPE_ID(CustomComponentId::CustomDebugDraw);

	void Initialize() override;
	void Terminate() override;
	void Deserialize(const rapidjson::Value& value) override;

	void AddDebugDraw() const;

private:
	const ThanksEngine::TransformComponent* mTransformComponent = nullptr;
	ThanksEngine::Math::Vector3 mPosition = ThanksEngine::Math::Vector3::Zero;
	ThanksEngine::Color mColor = ThanksEngine::Colors::White;

	uint32_t mSlices = 0;
	uint32_t mRings = 0;
	float mRadius = 0.0f;
};