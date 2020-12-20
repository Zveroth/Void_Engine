#include "vdpch.h"
#include "Scene.h"
#include "Void/Utility/CoreUtility.h"
#include "Renderer/Renderer2D.h"



Scene::~Scene()
{
	for (auto It = m_Pools.begin(); It != m_Pools.end(); It++)
		delete It->second;
}

void Scene::DeleteEntity(const Entity& Ent)
{
	int32_t Index = BinarySearch(m_Entities, Ent.m_ID);
	VD_CORE_ASSERT(Index != INDEX_NONE, "Removing not owned entity!");
	m_Entities.erase(m_Entities.begin() + Index);
}

void Scene::DeleteComponent(Entity& Ent, size_t ComponentClass)
{
	VD_CORE_ASSERT(m_Pools.find(ComponentClass) != m_Pools.end(), "Deletion of non existing component!");

	m_Pools[ComponentClass]->Delete(Ent.m_ID);
}

void Scene::Tick(float DeltaTime)
{
	//TODO: What when we don't have an active camera
	if (HasActiveCamera())
	{
		Renderer2D::BeginScene(GetActiveCamera());

		for (auto It = m_Pools.begin(); It != m_Pools.end(); It++)
			It->second->Tick(DeltaTime);

		Renderer2D::EndScene();
	}
}

CameraComponent& Scene::GetActiveCamera()
{
	VD_CORE_ASSERT(HasActiveCamera(), "Getting a non existing camera form a scene");
	return ((ComponentPool<CameraComponent>*)m_Pools.at(typeid(CameraComponent).hash_code()))->Get(m_ActiveCamera);
}

void Scene::SetActiveCamera(const CameraComponent& ActiveCamera)
{
	m_ActiveCamera = ActiveCamera.GetOwnerID();
}

void Scene::OnEvent(Event& e)
{
	EventDispatcher Dispatcher(e);
	Dispatcher.Dispatch<WindowResizeEvent>(VD_BIND_EVENT_FUN(Scene::OnWindowResized));
	Dispatcher.Dispatch<MouseScrolledEvent>(VD_BIND_EVENT_FUN(Scene::OnMouseScrolled));
}

bool Scene::OnWindowResized(WindowResizeEvent& e)
{
	if (HasActiveCamera())
		GetActiveCamera().GetCamera().SetAspectRatio(e.GetWidth() / e.GetHeight());

	return false;
}

bool Scene::OnMouseScrolled(MouseScrolledEvent& e)
{
	m_CameraZoom -= e.GetYOffset() * 0.25f;

	if (HasActiveCamera())
		GetActiveCamera().GetCamera().SetZoomLevel(m_CameraZoom);

	return false;
}