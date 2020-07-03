workspace "Polaroid"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Polaroid/vendor/GLFW/include"

include "Polaroid/vendor/GLFW"

project "Polaroid"
	location "Polaroid"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "plpch.h"
	pchsource "Polaroid/src/plpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PL_PLATFORM_WINDOWS",
			"PL_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		filter "configurations:Debug"
			defines "PL_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "PL_RELEASE"
			optimize "On"  

		filter "configurations:Dist"
			defines "PL_DEBUG"
			optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Polaroid/vendor/spdlog/include",
		"Polaroid/src"
	}

	links
	{
		"Polaroid"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PL_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "PL_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "PL_RELEASE"
			optimize "On"  

		filter "configurations:Dist"
			defines "PL_DEBUG"
			optimize "On"