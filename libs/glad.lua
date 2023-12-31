project "GLAD"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    architecture "x86_64"

    targetdir "../build/bin/%{cfg.buildcfg}"
    objdir "../build/obj/%{cfg.buildcfg}"

    includedirs { "glad/include/" }

    files { "glad/src/glad.c" }

    filter "system:windows"
    systemversion "latest"
    staticruntime "On"

    defines 
    { 
        "_GLAD_WIN32",
        "_CRT_SECURE_NO_WARNINGS"
    }

filter "configurations:Debug"
    runtime "Debug"
    symbols "on"

filter "configurations:Release"
    runtime "Release"
    optimize "on"