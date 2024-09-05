#include "GameState.h"

using namespace ThanksEngine;
using namespace ThanksEngine::Math;
using namespace ThanksEngine::Graphics;
using namespace ThanksEngine::Core;
using namespace ThanksEngine::Input;

const char* gDrawType[] =
{
	"None",
	"Line",
	"Sphere",
	"AABB",
	"FilledAABB",
	"GroundCircle",
	"Pyramid"
};

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
}

void GameState::Terminate()
{
}

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
}

void GameState::UpdateCamera(float deltaTime)
{
	auto input = InputSystem::Get();
	const float moveSpeed = (input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f) * deltaTime;
	const float turnSpeed = 0.1f * deltaTime;
	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed);
	}
}

Vector3 v0 = Vector3::Zero;
Vector3 v1 = Vector3::One;
Vector3 p0 = { -0.5f, 0.0f, 0.5f };
Vector3 p1 = { 0.5f, 0.0f, 0.5f };
Vector3 p2 = { 0.0f, 0.0f, -0.5f };
Vector3 p3 = { 0.0f, 1.0f, 0.0f };
int slices = 30;
int rings = 30;
float radius = 1.0f;
int slicesC = 30;
float radiusC = 1.0f;
Vector3 position = Vector3::Zero;
Vector3 minExtents = -Vector3::One;
Vector3 maxExtents = Vector3::One;
Vector3 minExtentsF = -Vector3::One;
Vector3 maxExtentsF = Vector3::One;
Color lineColor = Colors::Green;
void GameState::Render()
{
	if (mDebugDrawType == DebugDrawType::Sphere)
	{
		SimpleDraw::AddSphere(slices, rings, radius, position, lineColor);
	}
	else if (mDebugDrawType == DebugDrawType::Line)
	{
		SimpleDraw::AddLine(v0, v1, lineColor);
	}
	else if (mDebugDrawType == DebugDrawType::AABB)
	{
		SimpleDraw::AddAABB(minExtents, maxExtents, lineColor);
	}
	else if (mDebugDrawType == DebugDrawType::FilledAABB)
	{
		SimpleDraw::AddFilledAABB(minExtentsF, maxExtentsF, lineColor);
	}
	else if (mDebugDrawType == DebugDrawType::GroundCircle)
	{
		SimpleDraw::AddGroundCircle(slicesC, radiusC, lineColor);
	}
	else if (mDebugDrawType == DebugDrawType::Pyramid)
	{
		SimpleDraw::AddLine(p0, p1, lineColor);
		SimpleDraw::AddLine(p0, p2, lineColor);
		SimpleDraw::AddLine(p0, p3, lineColor);
		SimpleDraw::AddLine(p1, p2, lineColor);
		SimpleDraw::AddLine(p1, p3, lineColor);
		SimpleDraw::AddLine(p2, p3, lineColor);
	}
	SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	int currentDrawType = static_cast<int>(mDebugDrawType);
	if (ImGui::Combo("Draw Type", &currentDrawType, gDrawType, static_cast<int>(std::size(gDrawType))))
	{
		mDebugDrawType = (DebugDrawType)currentDrawType;
	}
	if (mDebugDrawType == DebugDrawType::Sphere)
	{
		ImGui::DragInt("Slices", &slices, 0.1f, 3, 100);
		ImGui::DragInt("Rings", &rings, 0.1f, 3, 100);
		ImGui::DragFloat("Radius", &radius, 0.01f);
		ImGui::DragFloat3("Position", &position.x, 0.1f);
	}
	else if (mDebugDrawType == DebugDrawType::GroundCircle)
	{
		ImGui::DragInt("Slices", &slicesC, 0.1f, 3, 100);
		ImGui::DragFloat("Radius", &radiusC, 0.01f);
	}
	else if (mDebugDrawType == DebugDrawType::AABB)
	{
		ImGui::DragFloat3("Min Extents", &minExtents.x, 0.1f);
		ImGui::DragFloat3("Max Extents", &maxExtents.x, 0.1f);
	}
	else if (mDebugDrawType == DebugDrawType::FilledAABB)
	{
		ImGui::DragFloat3("Min Extents", &minExtentsF.x, 0.1f);
		ImGui::DragFloat3("Max Extents", &maxExtentsF.x, 0.1f);
	}
	else if (mDebugDrawType == DebugDrawType::Line)
	{
		ImGui::DragFloat3("Point 1", &v0.x, 0.1f);
		ImGui::DragFloat3("Point 2", &v1.x, 0.1f);
		ImGui::ColorEdit4("Color", &lineColor.r);
	}
	else if (mDebugDrawType == DebugDrawType::Pyramid)
	{
		ImGui::DragFloat3("Point 1", &p0.x, 0.1f);
		ImGui::DragFloat3("Point 2", &p1.x, 0.1f);
		ImGui::DragFloat3("Point 3", &p2.x, 0.1f);
		ImGui::DragFloat3("Point 4", &p3.x, 0.1f);
		ImGui::ColorEdit4("Color", &lineColor.r);
	}
	else if (mDebugDrawType == DebugDrawType::None)
	{
		ImGui::Text("Select a draw type");
	}
	ImGui::ColorEdit4("Color", &lineColor.r);
	ImGui::End();
}
