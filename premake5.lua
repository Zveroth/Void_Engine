workspace "Void"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

OutputDir =  "%{cfg.system}_%{cfg.buildcfg}_%{cfg.architecture}"

project "Void"
	location "Void"
	kind "sharedLib"
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
		"%{prj.name}/3rdParty/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines
	{
		"VD_PLATFORM_WINDOWS",
		"VD_BUILD_DLL"
	}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. OutputDir .. "/Sandbox")
	}


	filter "configurations:Debug"
		defines "VD_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "VD_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "VD_DISTRIBUTION"
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
		defines "VD_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "VD_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "VD_DISTRIBUTION"
		optimize "On"