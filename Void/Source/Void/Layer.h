#pragma once

#include "Core.h"
#include "Events/Event.h"




class VD_API Layer
{

public:

	Layer(const std::string& DebugName = "Layer");
	virtual ~Layer();

	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnUpdate();
	virtual void OnEvent(Event& e) {}

	inline const std::string& GetName() const { return m_DebugName; }

protected:

	std::string m_DebugName;
};