#include "BulletPoolService.h"
#include "BulletComponent.h"

using namespace ThanksEngine;
using namespace ThanksEngine::Graphics;

void BulletPoolService::Register(BulletComponent* bulletComponent)
{
    auto iter = std::find(mBulletComponents.begin(),
        mBulletComponents.end(), bulletComponent);
    if (iter == mBulletComponents.end())
    {
        mBulletComponents.push_back(bulletComponent);
    }
}

void BulletPoolService::Unregister(BulletComponent* bulletComponent)
{
    auto iter = std::find(mBulletComponents.begin(),
        mBulletComponents.end(), bulletComponent);
    if (iter != mBulletComponents.end())
    {
        mBulletComponents.erase(iter);
    }
}

BulletComponent* BulletPoolService::GetNextBulletComponent()
{
	BulletComponent* bulletComponent = nullptr;
	if (mNextBulletIndex < mBulletComponents.size())
	{
		bulletComponent = mBulletComponents[mNextBulletIndex];
		mNextBulletIndex++;
	}
	else
	{
		mNextBulletIndex = 0;
		bulletComponent = mBulletComponents[mNextBulletIndex];
		mNextBulletIndex++;
	}
	bulletComponent->Reset();
	return bulletComponent;
}