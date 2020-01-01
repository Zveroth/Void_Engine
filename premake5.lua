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
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir("bin/" .. OutputDir .. "/%{prj.name}")
	objdir("intermediates/" .. OutputDir .. "/%{prj.name}")

	pchheader "vdpch.h"
	pchsource "Void/Source/vdpch.cpp"

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/Source",
		"%{prj.name}/3rdParty/spdlog/include",
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
		cppdialect "C++17"
		systemversion "latest"

	defines
	{
		"VD_PLATFORM_WINDOWS",
		"VD_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
	}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. OutputDir .. "/Sandbox")
	}


	filter "configurations:Debug"
		defines { "VD_DEBUG", "VD_ENABLE_ASSERTS" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "VD_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "VD_DISTRIBUTION"
		runtime "Release"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		cppdialect "C++17"
		systemversion "latest"

	defines
	{
		"VD_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		defines { "VD_DEBUG", "VD_ENABLE_ASSERTS" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "VD_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "VD_DISTRIBUTION"
		runtime "Release"
		optimize "On"