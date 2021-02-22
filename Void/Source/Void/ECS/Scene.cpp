#include "vdpch.h"
#include "Scene.h"
#include "Renderer/Renderer2D.h"
#include "ComponentBase.h"
#include "EntityBase.h"

#include "Void/ECS/Entities/EditorEntity.h"
#include "Void/ECS/Components/CameraComponent.h"



Scene::Scene() : m_Registry(CreateUnique<ECSRegistry>()), m_DefaultEntity(new VEditorEntity())
{
	m_DefaultEntity->Init(this, "EditorEntity");

	m_ActiveCamera = m_DefaultEntity->m_Camera;
	m_ActiveCamera->SetIsActive(true);
	m_ActiveCamera->SetAspectRatio(m_ViewportAspectRatio);
}

Scene::~Scene()
{
	delete m_DefaultEntity;
}

void Scene::Tick(float DeltaTime)
{
	Renderer2D::BeginScene(m_ActiveCamera->GetCamera().GetProjection(), m_ActiveCamera->GetView());

	m_Registry->ForEachComponent([DeltaTime](void* Component) {((ComponentBase*)Component)->Tick(DeltaTime); });

	Renderer2D::EndScene();

	if (m_bReloadEntities)
	{
		m_EntitiesCache.Empty();
		m_Registry->ForEachEntity([this](void* Object) { m_EntitiesCache.Emplace((EntityBase*)Object); });
		m_bReloadEntities = false;
	}
}

void Scene::DeleteEntity(EntityBase* Entity)
{
	m_Registry->DeleteEntity(Entity);
	m_bReloadEntities = true;
}

void Scene::DeleteComponent(ComponentBase* Component)
{
	m_Registry->DeleteComponent(Component);
}

DynamicArray<EntityBase*> Scene::GetEntities() const
{
	return m_EntitiesCache;
}

void Scene::OnEvent(Event& e)
{
	EventDispatcher Dispatcher(e);
	Dispatcher.Dispatch<MouseScrolledEvent>(VD_BIND_EVENT_FUN(Scene::OnMouseScrolled));
}

bool Scene::OnMouseScrolled(MouseScrolledEvent& e)
{
	m_ActiveCamera->SetOrthoWidth(m_ActiveCamera->GetOrthoWidth() - e.GetYOffset() * 0.25f);

	return false;
}

void Scene::SetActiveCamera(CameraComponent* ActivatedCamera)
{
	m_ActiveCamera->SetIsActive(false);

	m_ActiveCamera = ActivatedCamera;
	m_ActiveCamera->SetIsActive(true);
	m_ActiveCamera->SetAspectRatio(m_ViewportAspectRatio);
}

void Scene::InvalidateActiveCamera()
{
	m_ActiveCamera->SetIsActive(false);

	m_ActiveCamera = m_DefaultEntity->m_Camera;
	m_ActiveCamera->SetIsActive(true);
	m_ActiveCamera->SetAspectRatio(m_ViewportAspectRatio);
}

void Scene::SetViewportAspectRatio(float AspectRatio)
{
	m_ViewportAspectRatio = AspectRatio;

	m_ActiveCamera->SetAspectRatio(AspectRatio);
}

void Scene::SetViewportAspectRatio(float Width, float Height)
{
	SetViewportAspectRatio(Width / Height);
}