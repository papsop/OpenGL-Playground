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
        "libs/imgui/imgui/",
        "libs/spdlog/include",
    }

    vpaths { 
        ["Headers/"] = "**.h",
        ["Sources/"] = { "**.c", "**.cpp"},
    }

    files { "src/GLCore/**.cpp", "src/GLCore/**.h"}

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
        ["Headers/"] = "**.h",
        ["Sources/"] = { "**.c", "**.cpp"},
    }

    files { "src/GLSandbox/**.cpp", "src/GLSandbox/**.h"}

    links { "GLCore" }

    filter "system:windows"
    defines { "_WINDOWS", "GLFW_INCLUDE_NONE",}

group "Dependencies"
    includeexternal "libs/glfw.lua"
    includeexternal "libs/glad.lua"
    includeexternal "libs/glm.lua"
    includeexternal "libs/imgui.lua"
    -- spdlog works as header only, no need to make it into a static library
group ""