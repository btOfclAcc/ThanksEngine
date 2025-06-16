#include "CustomParticleComponent.h"
#include "CustomParticleService.h"

using namespace ThanksEngine;
using namespace ThanksEngine::Graphics;
using namespace ThanksEngine::Math;
using namespace ThanksEngine::Physics;

void CustomParticleComponent::Initialize()
{
	ParticleSystemInfo info;
	info.textureId = TextureCache::Get()->LoadTexture(mTextureFile);
	info.maxParticles = mMaxParticles;
	info.particlesPerEmit = mParticlesPerEmit;
	info.delay = mDelay;
	info.lifeTime = mLifeTime;
	info.timeBetweenEmit = mTimeBetweenEmit;
	info.spawnAngle = mSpawnAngle;
	info.spawnSpeed = mSpawnSpeed;
	info.spawnLifeTime = mSpawnLifeTime;
	info.spawnDirection = mSpawnDirection;
	info.spawnPosition = mSpawnPosition;
	info.startScale = mStartScale;
	info.endScale = mEndScale;
	info.startColor = mStartColor;
	info.endColor = mEndColor;
	info.particleMass = mParticleMass;
	mParticleSystem.Initialize(info);

	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	CustomParticleService* cps = GetOwner().GetWorld().GetService<CustomParticleService>();
	cps->Register(this);
}

void CustomParticleComponent::Terminate()
{
	mParticleSystem.Terminate();
	CustomParticleService* cps = GetOwner().GetWorld().GetService<CustomParticleService>();
	cps->Unregister(this);
}

void CustomParticleComponent::Update(float deltaTime)
{
	mParticleSystem.SetPosition(mTransformComponent->position);
	if (mParticleSystem.IsActive())
	{
		mParticleSystem.Update(deltaTime);
	}
}

void CustomParticleComponent::Deserialize(const rapidjson::Value& value)
{
	if (value.HasMember("TextureFile"))
	{
		mTextureFile = value["TextureFile"].GetString();
	}
	if (value.HasMember("MaxParticles"))
	{
		mMaxParticles = value["MaxParticles"].GetInt();
	}
	if (value.HasMember("ParticlesPerEmit"))
	{
		auto particlesPerEmit = value["ParticlesPerEmit"].GetArray();
		mParticlesPerEmit.min = particlesPerEmit[0].GetInt();
		mParticlesPerEmit.max = particlesPerEmit[1].GetInt();
	}
	if (value.HasMember("Delay"))
	{
		mDelay = value["Delay"].GetFloat();
	}
	if (value.HasMember("LifeTime"))
	{
		mLifeTime = value["LifeTime"].GetFloat();
	}
	if (value.HasMember("TimeBetweenEmit"))
	{
		auto timeBetweenEmit = value["TimeBetweenEmit"].GetArray();
		mTimeBetweenEmit.min = timeBetweenEmit[0].GetFloat();
		mTimeBetweenEmit.max = timeBetweenEmit[1].GetFloat();
	}
	if (value.HasMember("SpawnAngle"))
	{
		auto spawnAngle = value["SpawnAngle"].GetArray();
		mSpawnAngle.min = spawnAngle[0].GetFloat();
		mSpawnAngle.max = spawnAngle[1].GetFloat();
	}
	if (value.HasMember("SpawnSpeed"))
	{
		auto spawnSpeed = value["SpawnSpeed"].GetArray();
		mSpawnSpeed.min = spawnSpeed[0].GetFloat();
		mSpawnSpeed.max = spawnSpeed[1].GetFloat();
	}
	if (value.HasMember("SpawnLifeTime"))
	{
		auto spawnLifeTime = value["SpawnLifeTime"].GetArray();
		mSpawnLifeTime.min = spawnLifeTime[0].GetFloat();
		mSpawnLifeTime.max = spawnLifeTime[1].GetFloat();
	}
	if (value.HasMember("SpawnDirection"))
	{
		auto spawnDirection = value["SpawnDirection"].GetArray();
		mSpawnDirection.x = spawnDirection[0].GetFloat();
		mSpawnDirection.y = spawnDirection[1].GetFloat();
		mSpawnDirection.z = spawnDirection[2].GetFloat();
	}
	if (value.HasMember("SpawnPosition"))
	{
		auto spawnPosition = value["SpawnPosition"].GetArray();
		mSpawnPosition.x = spawnPosition[0].GetFloat();
		mSpawnPosition.y = spawnPosition[1].GetFloat();
		mSpawnPosition.z = spawnPosition[2].GetFloat();
	}
	if (value.HasMember("StartScaleMin"))
	{
		auto startScale = value["StartScaleMin"].GetArray();
		mStartScale.min.x = startScale[0].GetFloat();
		mStartScale.min.y = startScale[1].GetFloat();
		mStartScale.min.z = startScale[2].GetFloat();
	}
	if (value.HasMember("StartScaleMax"))
	{
		auto startScale = value["StartScaleMax"].GetArray();
		mStartScale.max.x = startScale[0].GetFloat();
		mStartScale.max.y = startScale[1].GetFloat();
		mStartScale.max.z = startScale[2].GetFloat();
	}
	if (value.HasMember("EndScaleMin"))
	{
		auto endScale = value["EndScaleMin"].GetArray();
		mEndScale.min.x = endScale[0].GetFloat();
		mEndScale.min.y = endScale[1].GetFloat();
		mEndScale.min.z = endScale[2].GetFloat();
	}
	if (value.HasMember("EndScaleMax"))
	{
		auto endScale = value["EndScaleMax"].GetArray();
		mEndScale.max.x = endScale[0].GetFloat();
		mEndScale.max.y = endScale[1].GetFloat();
		mEndScale.max.z = endScale[2].GetFloat();
	}
	if (value.HasMember("StartColorMin"))
	{
		auto startColor = value["StartColorMin"].GetArray();
		mStartColor.min.r = startColor[0].GetFloat();
		mStartColor.min.g = startColor[1].GetFloat();
		mStartColor.min.b = startColor[2].GetFloat();
		mStartColor.min.a = startColor[3].GetFloat();
	}
	if (value.HasMember("StartColorMax"))
	{
		auto startColor = value["StartColorMax"].GetArray();
		mStartColor.max.r = startColor[0].GetFloat();
		mStartColor.max.g = startColor[1].GetFloat();
		mStartColor.max.b = startColor[2].GetFloat();
		mStartColor.max.a = startColor[3].GetFloat();
	}
	if (value.HasMember("EndColorMin"))
	{
		auto endColor = value["EndColorMin"].GetArray();
		mEndColor.min.r = endColor[0].GetFloat();
		mEndColor.min.g = endColor[1].GetFloat();
		mEndColor.min.b = endColor[2].GetFloat();
		mEndColor.min.a = endColor[3].GetFloat();
	}
	if (value.HasMember("EndColorMax"))
	{
		auto endColor = value["EndColorMax"].GetArray();
		mEndColor.max.r = endColor[0].GetFloat();
		mEndColor.max.g = endColor[1].GetFloat();
		mEndColor.max.b = endColor[2].GetFloat();
		mEndColor.max.a = endColor[3].GetFloat();
	}
	if (value.HasMember("ParticleMass"))
	{
		mParticleMass = value["ParticleMass"].GetFloat();
	}
}

void CustomParticleComponent::SetSpawnOverride(bool override)
{
	mParticleSystem.SetSpawnOverride(override);
}

void CustomParticleComponent::SetActiveOverride(bool override)
{
	mParticleSystem.SetActiveOverride(override);
}