workspace "OpenGL_Playground"
    configurations { "Debug", "Release" }
    startproject "GLSandbox"
    location "project/"
    flags { "MultiProcessorCompile" }

project "GLCore"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    architecture "x86_64"

    targetdir "build/bin/%{cfg.buildcfg}"
    objdir "build/obj/%{cfg.buildcfg}"

    includedirs
    {
        "src/",
        "libs/glad/include/",
        "libs/glfw/include/",
        "libs/glm/",
        "libs/imgui/",
        "libs/spdlog/include",
    }

    vpaths { 
        ["Headers/"] = { "**.h", "**.inl" },
        ["Sources/"] = { "**.c", "**.cpp"},
    }

    files { "src/GLCore/**.cpp", "src/GLCore/**.h", "src/GLCore/**.inl"}

    links { "GLFW", "GLM", "GLAD", "ImGui" }

    filter "system:windows"
    defines { "_WINDOWS", "GLFW_INCLUDE_NONE", "SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE" }

project "GLSandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    architecture "x86_64"
    targetdir "build/bin/%{cfg.buildcfg}"
    objdir "build/obj/%{cfg.buildcfg}"

    includedirs
    {
        "src/",
        "libs/glad/include/",
        "libs/glfw/include/",
        "libs/glm/",
        "libs/imgui/",
        "libs/spdlog/include/",
    }

    vpaths { 
        ["Headers/"] = { "**.h", "**.inl" },
        ["Sources/"] = { "**.c", "**.cpp"},
    }

    files { "src/GLSandbox/**.cpp", "src/GLSandbox/**.h", "src/GLSandbox/**.inl"}

    links { "GLCore" }

    filter "system:windows"
        defines { "_WINDOWS", "GLFW_INCLUDE_NONE",}

group "Dependencies"
    include "libs/glfw.lua"
    include "libs/glad.lua"
    include "libs/glm.lua"
    include "libs/imgui.lua"
    -- spdlog works as header only, no need to make it into a static library
group ""