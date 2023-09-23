project "ImGui"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	architecture "x86_64"
	staticruntime "on"

	targetdir "../build/bin/%{cfg.buildcfg}"
	objdir "../build/obj/%{cfg.buildcfg}"
	
	includedirs { "imgui/", "glad/include", "glfw/include/" }

	files
	{
		"imgui/imconfig.h",
		"imgui/imgui.h",
		"imgui/imgui.cpp",
		"imgui/imgui_draw.cpp",
		"imgui/imgui_internal.h",
		"imgui/imgui_widgets.cpp",
		"imgui/imgui_tables.cpp",
		"imgui/imstb_rectpack.h",
		"imgui/imstb_textedit.h",
		"imgui/imstb_truetype.h",
		"imgui/imgui_demo.cpp",
		"imgui/imgui_impl_glfw.h",
		"imgui/imgui_impl_glfw.cpp",
		"imgui/imgui_impl_opengl3.h",
		"imgui/imgui_impl_opengl3_loader.h",
		"imgui/imgui_impl_opengl3.cpp",
	}

	defines 
	{
		"IMGUI_IMPL_OPENGL_LOADER_GLAD"
	}
    
	filter "system:linux"
		pic "On"

		systemversion "latest"
		staticruntime "On"

		defines
		{
			"_IMGUI_X11"
		}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		defines 
		{ 
			"_IMGUI_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"