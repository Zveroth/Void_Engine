#pragma once
#include "Components/Component.h"
#include "Void/Events/MouseEvent.h"



class ECSRegistry;
class CameraComponent;

class Scene
{
	
public:

	Scene();

	void PostInit();

	void Tick(float DeltaTime);

	bool HasActiveCamera() const { return m_ActiveCamera > 1; }
	CameraComponent& GetActiveCamera();
	void SetActiveCamera(CameraComponent& ActiveCamera);
	void InvalidateActiveCamera();

	void SetViewportAspectRatio(float AspectRatio);
	void SetViewportAspectRatio(float Width, float Height);

	void OnEvent(Event& e);

	bool OnMouseScrolled(MouseScrolledEvent& e);

	ECSRegistry* GetRegistry() { return m_Registry.get(); }

	template<typename T>
	T* AddEntity(const std::string& Name = "Unnamed_Entity")
	{
		T* Ent = m_Registry->AddEntity<T>(Name);
		Ent->Init(this);
		return Ent;
	}

private:

	uint32_t m_ActiveCamera = 1;
	float m_ViewportAspectRatio = 16.0f / 9.0f;

	UniqueRef<ECSRegistry> m_Registry;
};