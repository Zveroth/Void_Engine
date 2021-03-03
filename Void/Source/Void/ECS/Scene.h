#pragma once
#include "Void/Events/MouseEvent.h"
#include "ECSRegistry.h"



class EntityBase;
class ComponentBase;
class CameraComponent;

class Scene
{
	
public:

	Scene();
	~Scene();

	void Tick(float DeltaTime);

	template<typename T, typename... Args>
	ControlledPointer<T> CreateEntity(const std::string& Name = "Unnamed_Entity", Args &&... args)
	{
		ControlledPointer<T> Ent = m_Registry->CreateEntity<T>(std::forward<Args>(args)...);
		m_EntitiesCache.Emplace(ControlledPointer<EntityBase>((EntityBase*)Ent.Get(), Ent.GetBit()));
		Ent->m_InternalValidationBit = Ent.GetBit();
		Ent->Init(this, Name + '_' + std::to_string(m_NameModifier));
		++m_NameModifier;

		m_bReloadEntities = true;
		return Ent;
	}

	template<typename T, typename... Args>
	ControlledPointer<T> CreateComponent(Args &&... args)
	{
		return m_Registry->CreateComponent<T>(std::forward<Args>(args)...);
	}

	void DeleteEntity(EntityBase* Entity);
	void DeleteComponent(ComponentBase* Component);

	const DynamicArray<ControlledPointer<EntityBase>>& GetEntities() const;

	CameraComponent* GetActiveCamera() const noexcept { return m_ActiveCamera; }
	void SetActiveCamera(CameraComponent* ActivatedCamera);
	void InvalidateActiveCamera();
	void SetViewportAspectRatio(float AspectRatio);
	void SetViewportAspectRatio(float Width, float Height);

	void OnEvent(Event& e);
	bool OnMouseScrolled(MouseScrolledEvent& e);

private:

	UniqueRef<ECSRegistry> m_Registry;
	uint32_t m_NameModifier = 0;

	DynamicArray<ControlledPointer<EntityBase>> m_EntitiesCache;
	bool m_bReloadEntities = false;

	class VEditorEntity* m_DefaultEntity;

	CameraComponent* m_ActiveCamera = nullptr;
	float m_ViewportAspectRatio = 16.0f / 9.0f;
};