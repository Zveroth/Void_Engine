#include "vdpch.h"
#include "EditorCamera.h"
#include "Void/ECS/Components/CameraComponent.h"
#include "Void/Core/Input.h"



void EditorCamera::PostInit()
{
	AddComponent<CameraComponent>();
}

void EditorCamera::Tick(float DeltaTime)
{
	CameraComponent& CameraComp = GetComponent<CameraComponent>();

	if (Input::IsKeyPressed(VD_KEY_A))
		CameraComp.AddLocationOffset({ -1.0f * DeltaTime, 0.0f, 0.0f });
	else if (Input::IsKeyPressed(VD_KEY_D))
		CameraComp.AddLocationOffset({ 1.0f * DeltaTime, 0.0f, 0.0f });

	if (Input::IsKeyPressed(VD_KEY_W))
		CameraComp.AddLocationOffset({ 0.0f, 1.0f * DeltaTime, 0.0f });
	else if (Input::IsKeyPressed(VD_KEY_S))
		CameraComp.AddLocationOffset({ 0.0f, -1.0f * DeltaTime, 0.0f });
}