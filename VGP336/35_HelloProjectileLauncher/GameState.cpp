#include "GameState.h"

#include "BulletComponent.h"
#include "CustomParticleComponent.h"
#include "ExplosionComponent.h"
#include "FiringLogicComponent.h"

#include "BulletPoolService.h"
#include "CustomParticleService.h"

using namespace ThanksEngine;
using namespace ThanksEngine::Math;
using namespace ThanksEngine::Graphics;
using namespace ThanksEngine::Core;
using namespace ThanksEngine::Input;
using namespace ThanksEngine::Audio;

Service* CustomServiceMake(const std::string& serviceName, GameWorld& gameWorld)
{
	if (serviceName == "BulletPoolService")
	{
		return gameWorld.AddService<BulletPoolService>();
	}
	if (serviceName == "CustomParticleService")
	{
		return gameWorld.AddService<CustomParticleService>();
	}
	return nullptr;
}

Component* CustomComponentMake(const std::string& componentName, GameObject& gameObject)
{
	if (componentName == "BulletComponent")
	{
		return gameObject.AddComponent<BulletComponent>();
	}
	if (componentName == "CustomParticleComponent")
	{
		return gameObject.AddComponent<CustomParticleComponent>();
	}
	if (componentName == "ExplosionComponent")
	{
		return gameObject.AddComponent<ExplosionComponent>();
	}
	if (componentName == "FiringLogicComponent")
	{
		return gameObject.AddComponent<FiringLogicComponent>();
	}
	return nullptr;
}

Component* CustomComponentGet(const std::string& componentName, GameObject& gameObject)
{
	if (componentName == "BulletComponent")
	{
		return gameObject.GetComponent<BulletComponent>();
	}
	if (componentName == "CustomParticleComponent")
	{
		return gameObject.GetComponent<CustomParticleComponent>();
	}
	if (componentName == "ExplosionComponent")
	{
		return gameObject.GetComponent<ExplosionComponent>();
	}
	if (componentName == "FiringLogicComponent")
	{
		return gameObject.GetComponent<FiringLogicComponent>();
	}
	return nullptr;
}

void GameState::Initialize()
{
	GameWorld::SetCustomService(CustomServiceMake);
	GameObjectFactory::SetCustomMake(CustomComponentMake);
	GameObjectFactory::SetCustomGet(CustomComponentGet);

    mGameWorld.LoadLevel(L"../../Assets/Templates/Levels/projectile_level.json");
}

void GameState::Terminate()
{
    mGameWorld.Terminate();
}

void GameState::Update(float deltaTime)
{
    mGameWorld.Update(deltaTime);
}

void GameState::Render()
{
    mGameWorld.Render();
}

void GameState::DebugUI()
{
    ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    mGameWorld.DebugUI();
    ImGui::End();
}