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
IncludeDir["Glad"] = "Polaroid/vendor/Glad/include"
IncludeDir["ImGui"] = "Polaroid/vendor/imgui"

include "Polaroid/vendor/GLFW"
include "Polaroid/vendor/Glad"
include "Polaroid/vendor/ImGui"

project "Polaroid"
	location "Polaroid"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"PL_PLATFORM_WINDOWS",
			"PL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		filter "configurations:Debug"
			defines "PL_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "PL_RELEASE"
			runtime "Release"
			optimize "On"  

		filter "configurations:Dist"
			defines "PL_DIST"
			runtime "Release"
			optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		systemversion "latest"

		defines
		{
			"PL_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "PL_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "PL_RELEASE"
			runtime "Release"
			optimize "On"  

		filter "configurations:Dist"
			defines "PL_DIST"
			runtime "Release"
			optimize "On"