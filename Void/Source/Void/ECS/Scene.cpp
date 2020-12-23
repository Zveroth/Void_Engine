#include "vdpch.h"
#include "Scene.h"
#include "Components/CameraComponent.h"
#include "Entities/EditorCamera.h"
#include "ECSRegistry.h"



Scene::Scene() : m_Registry(CreateUnique<ECSRegistry>())
{

}

void Scene::PostInit()
{
	AddEntity<EditorCamera>("Default_Editor_Camera");
}

void Scene::Tick(float DeltaTime)
{
	m_Registry->Tick(GetActiveCamera(), DeltaTime);
}

CameraComponent& Scene::GetActiveCamera()
{
	if(HasActiveCamera())
		return m_Registry->GetPool<CameraComponent>(typeid(CameraComponent).hash_code())->Get(m_ActiveCamera);
	else
		return m_Registry->GetPool<CameraComponent>(typeid(CameraComponent).hash_code())->Get(1);
}

void Scene::SetActiveCamera(CameraComponent& ActiveCamera)
{
	if (HasActiveCamera())
		GetActiveCamera().SetIsActive(false);

	m_ActiveCamera = ActiveCamera.GetOwnerID();
	GetActiveCamera().SetIsActive(true);

	ActiveCamera.SetAspectRatio(m_ViewportAspectRatio);
}

void Scene::InvalidateActiveCamera()
{
	m_ActiveCamera = 0;

	GetActiveCamera().SetAspectRatio(m_ViewportAspectRatio);
}

void Scene::SetViewportAspectRatio(float AspectRatio)
{
	m_ViewportAspectRatio = AspectRatio;

	GetActiveCamera().SetAspectRatio(AspectRatio);
}

void Scene::SetViewportAspectRatio(float Width, float Height)
{
	SetViewportAspectRatio(Width / Height);
}

void Scene::OnEvent(Event& e)
{
	EventDispatcher Dispatcher(e);
	Dispatcher.Dispatch<MouseScrolledEvent>(VD_BIND_EVENT_FUN(Scene::OnMouseScrolled));
}

bool Scene::OnMouseScrolled(MouseScrolledEvent& e)
{
	//Apply zoom only to editor camera
	if (!HasActiveCamera())
	{
		CameraComponent& ActiveCamera = GetActiveCamera();
		float Zoom = ActiveCamera.GetZoomLevel();
		Zoom -= e.GetYOffset() * 0.25f;
		GetActiveCamera().SetZoomLevel(Zoom);
	}

	return false;
}