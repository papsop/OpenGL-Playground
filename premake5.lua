workspace "OpenGL-Playground"
    configurations { "Debug", "Release" }
    startproject "OpenGL-Playground"
    location "project/"

project "OpenGL-Playground"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    architecture "x86_64"

    targetdir "build/bin/%{cfg.buildcfg}"
    objdir "build/obj/%{cfg.buildcfg}"

    includedirs
    {
        "include/",
        "libs/glad/include/",
        "libs/glfw/include/",
        "libs/glm/",
        "libs/imgui/",        
    }

    files { "src/*.cpp" }

    links { "GLFW", "GLM", "GLAD", "ImGui"}

    filter "system:windows"
    defines { "_WINDOWS" }

group "Dependencies"
    include "libs/glfw.lua"
    include "libs/glad.lua"
    include "libs/glm.lua"
    include "libs/imgui.lua"