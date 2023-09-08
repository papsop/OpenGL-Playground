project "ImGui"
	kind "StaticLib"
	language "C"
	architecture "x86_64"

	targetdir "../build/bin/%{cfg.buildcfg}"
	objdir "../build/obj/%{cfg.buildcfg}"
	
	includedirs { "dearimgui/", "glad/include", "glfw/include/" }

	files
	{
		"dearimgui/imconfig.h",
		"dearimgui/imgui.h",
		"dearimgui/imgui.cpp",
		"dearimgui/imgui_draw.cpp",
		"dearimgui/imgui_internal.h",
		"dearimgui/imgui_widgets.cpp",
		"dearimgui/imstb_rectpack.h",
		"dearimgui/imstb_textedit.h",
		"dearimgui/imstb_truetype.h",
		"dearimgui/imgui_demo.cpp",
		"dearimgui/imgui_impl_glfw.h",
		"dearimgui/imgui_impl_glfw.cpp",
		"dearimgui/imgui_impl_opengl3.h",
		"dearimgui/imgui_impl_opengl3_loader.h",
		"dearimgui/imgui_impl_opengl3.cpp",
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