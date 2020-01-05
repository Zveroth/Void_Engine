#pragma once

#include "Core.h"
#include "Events/Event.h"




class  Layer
{

public:

	Layer(const std::string& DebugName = "Layer");
	virtual ~Layer();

	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate(const float& DeltaTime) {}
	virtual void OnImGuiRender() {}
	virtual void OnEvent(Event& e) {}

	inline const std::string& GetName() const { return m_DebugName; }

protected:

	std::string m_DebugName;
};