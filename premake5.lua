workspace "Engine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include dirs relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "Engine/vendor/Glad/include"
IncludeDir["ImGui"] = "Engine/vendor/imgui"
IncludeDir["glm"] = "Engine/vendor/glm"
IncludeDir["stb_image"] = "Engine/vendor/stb_image"

include "Engine/vendor/GLFW"
include "Engine/vendor/Glad"
include "Engine/vendor/imgui"

project "Engine"
	location "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "enpch.h"
	pchsource "Engine/src/enpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/Vulkan/include",
		"%{prj.name}/vendor/tiny_obj",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{prj.name}/vendor/openvr/include",
		"%{IncludeDir.stb_image}",
		
	}

	libdirs
	{
		"%{prj.name}/vendor/openvr/lib/win64",
		"%{prj.name}/vendor/Vulkan/lib"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"openvr_api.lib",
		"vulkan-1.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"EN_PLATFORM_WINDOWS",
			"EN_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS",
			"EN_ENABLE_ASSERTS"
		}

	filter "configurations:Debug"
		defines
		{
			"EN_DEBUG",
		}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EN_DIST"
		runtime "Release"
		optimize "on"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"

	}

	includedirs
	{
		"Engine/vendor/spdlog/include",
		"Engine/vendor/Vulkan/include",
		"Engine/vendor/tiny_obj",
		"Engine/src",
		"Engine/vendor/openvr/include",
		"Engine/vendor/Glad/include",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"Engine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"EN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "EN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EN_DIST"
		runtime "Release"
		optimize "on"