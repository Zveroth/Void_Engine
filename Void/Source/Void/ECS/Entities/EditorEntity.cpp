#include "vdpch.h"
#include "EditorEntity.h"



void VEditorEntity::PostInit()
{
	m_Camera = AddComponent<CameraComponent>();
}

void VEditorEntity::Tick(float DeltaTime)
{

}