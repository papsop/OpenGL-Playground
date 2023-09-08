#include <GLCore/Core/Application.h>
#include <GLCore/Core/Layer.h>
#include <GLCore/Layers/ImGuiOverlay.h>
#include <GLCore/Utils/Log.h>
#include <GLCore/Platform/WindowsWindow.h>

#include <GLFW/glfw3.h>

#include <iostream>

namespace GLCore {
Application::Application()
{
  GL_ASSERT(m_instance == nullptr, "Application already has an instance");
  Initialize();
}

Application::~Application()
{
}

Application& Application::Instance()
{
  return *m_instance;
}

void Application::Initialize()
{
  Log::Init();
  LOG_INFO("Initializing Application");
  InitGL();
  m_instance = this;
}

void Application::InitGL()
{
}

void Application::Run()
{
  // m_imGuiOverlay = new ImGuiOverlay();
  // m_layerStack.PushOverlay(m_imGuiOverlay);

#ifdef _WINDOWS
  LOG_INFO("Creating a WindowsWindow");
  m_window = std::make_unique<WindowsWindow>();
  m_window->Init(/* default */);
#else
#error "Platform not supported"
#endif

  float lastFrameTime = 0.0f;
  size_t frameCount = 0;

  while (m_isRunning) {
    frameCount++;
    float currentTime = static_cast<float>(glfwGetTime());
    Timestep ts = currentTime - lastFrameTime;
    lastFrameTime = currentTime;

    m_window->Update(ts);
  }

  m_window->Destroy();
}

}  // namespace GLCore
