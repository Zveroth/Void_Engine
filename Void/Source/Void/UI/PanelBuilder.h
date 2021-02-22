#pragma once

#include "glm/glm.hpp"



class VPanelBuilder
{

public:

	bool DrawCheckbox(const std::string& Label, bool* Value);

	void DrawFloat(const std::string& Label, float* Value, float Min = 0.0f, float Max = 0.0f);
	void DrawFloat_3(const std::string& Label, glm::vec3& Value, float Min = 0.0f, float Max = 0.0f);

	void DrawFloat(const std::string& Label, float Value, const std::function<void(float)>& Function, float Min = 0.0f, float Max = 0.0f);

	void DrawColor_4(const std::string& Label, glm::vec4& Value);
};