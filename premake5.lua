workspace "Void"
	architecture "x64"

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

include "3rdParty/GLFW"
include "3rdParty/GLAD"
include "3rdParty/ImGui"

project "Void"
	location "Void"
	kind "SharedLib"
	language "C++"

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
		"%{IncludeDir.ImGui}"
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
		staticruntime "On"
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
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "VD_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "VD_DISTRIBUTION"
		buildoptions "/MD"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Void/3rdParty/spdlog/include"
	}

	links
	{
		"Void"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines
	{
		"VD_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		defines { "VD_DEBUG", "VD_ENABLE_ASSERTS" }
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "VD_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "VD_DISTRIBUTION"
		buildoptions "/MD"
		optimize "On"