#pragma 

#include "glm/glm.hpp"



class UIHelpers
{

public:

	UIHelpers() = delete;

	static void EditVec3(const std::string& Label, glm::vec3& Values, float Min = 0.0f, float Max = 0.0f);
};