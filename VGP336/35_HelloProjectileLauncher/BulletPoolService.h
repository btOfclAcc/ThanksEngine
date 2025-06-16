#pragma once

#include "CustomTypeIds.h"

class BulletComponent;

class BulletPoolService : public ThanksEngine::Service
{
public:
    SET_TYPE_ID(CustomServiceId::BulletPool);

    void Register(BulletComponent* debugDrawComponent);
    void Unregister(BulletComponent* debugDrawComponent);

	BulletComponent* GetNextBulletComponent();

private:
    using BulletComponents = std::vector<BulletComponent*>;
    BulletComponents mBulletComponents;

	int mNextBulletIndex = 0;
};