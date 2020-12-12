workspace "Void"
	architecture "x64"
	startproject "VoidEditor"

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
		"%{prj.name}/3rdParty/assimp/include",
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
		"Void/3rdParty/assimp/include",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	libdirs
	{
		"%{prj.name}/../Void/3rdParty/assimp/lib"
	}

	links
	{
		"Void",
		"assimp-vc142-mt.lib"
	}

	filter "system:windows"
		systemversion "latest"

	defines
	{
		"VD_PLATFORM_WINDOWS"
	}

	postbuildcommands
	{
		("{COPY} ../Void/3rdParty/assimp/lib/assimp-vc142-mt.dll ../bin/" .. OutputDir .. "/Sandbox")
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


project "VoidEditor"
	location "VoidEditor"
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
		"Void/3rdParty/assimp/include",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	libdirs
	{
		"%{prj.name}/../Void/3rdParty/assimp/lib"
	}

	links
	{
		"Void",
		"assimp-vc142-mt.lib"
	}

	filter "system:windows"
		systemversion "latest"

	defines
	{
		"VD_PLATFORM_WINDOWS"
	}

	postbuildcommands
	{
		("{COPY} ../Void/3rdParty/assimp/lib/assimp-vc142-mt.dll ../bin/" .. OutputDir .. "/Sandbox")
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