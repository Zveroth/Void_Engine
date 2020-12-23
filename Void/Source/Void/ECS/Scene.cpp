#include "vdpch.h"
#include "Scene.h"
#include "Void/Utility/CoreUtility.h"
#include "Renderer/Renderer2D.h"
#include "Void/ECS/Entity.h"
#include "Entities/EditorCamera.h"



void Scene::PostInit()
{
	AddEntity<EditorCamera>("Default_Editor_Camera");
}

Scene::~Scene()
{
	for (auto It = m_Pools.begin(); It != m_Pools.end(); It++)
		delete It->second;

	for (Entity* Ent : m_Entities)
		delete Ent;
}

void Scene::DeleteEntity(const Entity& Ent)
{
	int32_t Index = BinarySearch(m_EntIDs, Ent.m_ID);
	VD_CORE_ASSERT(Index != INDEX_NONE, "Removing not owned entity!");

	m_EntIDs.erase(m_EntIDs.begin() + Index);
	m_Entities.erase(m_Entities.begin() + Index);
}

void Scene::DeleteComponent(Entity& Ent, size_t ComponentClass)
{
	VD_CORE_ASSERT(m_Pools.find(ComponentClass) != m_Pools.end(), "Deletion of non existing component!");

	m_Pools[ComponentClass]->DeleteDirect(Ent.m_ID);
}

void Scene::Tick(float DeltaTime)
{
	CameraComponent& ActiveCamera = GetActiveCamera();
	Renderer2D::BeginScene(ActiveCamera.GetCamera(), ActiveCamera.GetView());

	for (auto It = m_Pools.begin(); It != m_Pools.end(); It++)
		It->second->Tick(DeltaTime);

	Renderer2D::EndScene();
}

CameraComponent& Scene::GetActiveCamera()
{
	if(HasActiveCamera())
		return GetPool<CameraComponent>(typeid(CameraComponent).hash_code())->Get(m_ActiveCamera);
	else
		return GetPool<CameraComponent>(typeid(CameraComponent).hash_code())->Get(1);
}

void Scene::SetActiveCamera(CameraComponent& ActiveCamera)
{
	m_ActiveCamera = ActiveCamera.GetOwnerID();

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

Entity* Scene::GetEntity(uint32_t ID)
{
	int32_t Index = BinarySearch(m_EntIDs, ID);
	VD_CORE_ASSERT(Index != INDEX_NONE, "Entity with a given ID doesn't exist!");

	return m_Entities[ID];
}