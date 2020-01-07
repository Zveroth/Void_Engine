workspace "Void"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

OutputDir =  "%{cfg.system}_%{cfg.buildcfg}_%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "3rdParty/GLFW/include"
IncludeDir["GLAD"] = "3rdParty/GLAD/include"
IncludeDir["ImGui"] = "3rdParty/ImGui"
IncludeDir["glm"] = "3rdParty/glm"

group "Dependencies"
	include "3rdParty/GLFW"
	include "3rdParty/GLAD"
	include "3rdParty/ImGui"


group ""

project "Void"
	location "Void"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. OutputDir .. "/%{prj.name}")
	objdir("intermediates/" .. OutputDir .. "/%{prj.name}")

	pchheader "vdpch.h"
	pchsource "Void/Source/vdpch.cpp"

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
		"%{prj.name}/3rdParty/stb_image/**.h",
		"%{prj.name}/3rdParty/stb_image/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/Source",
		"%{prj.name}/3rdParty/spdlog/include",
		"%{prj.name}/3rdParty/stb_image",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

	defines
	{
		"VD_PLATFORM_WINDOWS",
		"VD_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
	}


	filter "configurations:Debug"
		defines { "VD_DEBUG", "VD_ENABLE_ASSERTS" }
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VD_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "VD_DISTRIBUTION"
		runtime "Release"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. OutputDir .. "/%{prj.name}")
	objdir("intermediates/" .. OutputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"Void/Source",
		"Void/3rdParty/spdlog/include",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Void"
	}

	filter "system:windows"
		systemversion "latest"

	defines
	{
		"VD_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		defines { "VD_DEBUG", "VD_ENABLE_ASSERTS" }
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VD_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "VD_DISTRIBUTION"
		runtime "Release"
		optimize "on"