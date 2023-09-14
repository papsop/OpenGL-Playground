#include <GLCore/Core/Application.h>
#include <GLCore/Core/Layer.h>
#include <GLCore/Core/Renderer.h>
#include <GLCore/Layers/ImGuiOverlay.h>
#include <GLCore/Layers/AppControlOverlay.h>
#include <GLCore/Layers/TriangleTestLayer.h>
#include <GLCore/Layers/ImGuiPanelRenderOverlay.h>
#include <GLCore/Utils/Log.h>
#include <GLCore/Platform/WindowsWindow.h>

#include <GLFW/glfw3.h>

#include <memory>
#include <iostream>

namespace GLCore {
Application::Application()
{
  GL_ASSERT(m_instance == nullptr, "Application already has an instance");
  Initialize();
}

Application::~Application()
{
  LOG_INFO("Destroying application.");
  m_renderer->Destroy();
  m_renderer = nullptr;
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
  m_renderer = std::make_unique<Renderer2D>();
  m_instance = this;
}

void Application::InitGL()
{
}

void Application::Run()
{
#ifdef _WINDOWS
  LOG_INFO("Creating a WindowsWindow");
  m_window = std::make_unique<WindowsWindow>();
  m_window->Init(/* default */);
#else
#error "Platform not supported"
#endif
  m_renderer->Create();
  m_layerStack.PushOverlay(new ImGuiOverlay());
  m_layerStack.PushOverlay(new AppControlOverlay());
  m_layerStack.PushOverlay(new ImGuiPanelRenderOverlay());

  m_layerStack.PushLayer(new TriangleTestLayer());

  float lastFrameTime = 0.0f;
  size_t frameCount = 0;

  while (m_isRunning) {
    frameCount++;
    float currentTime = static_cast<float>(glfwGetTime());
    Timestep ts = currentTime - lastFrameTime;
    lastFrameTime = currentTime;

    m_window->OnFrameBegin();

    // FRAME BEGIN
    for (auto* layer : m_layerStack) {
      if (layer->ShouldUpdate()) layer->OnFrameBegin();
    }

    // UPDATE
    for (auto* layer : m_layerStack) {
      if (layer->ShouldUpdate()) layer->OnUpdate(ts);
    }

    // IMGUI UPDATE
    for (auto* layer : m_layerStack) {
      if (layer->ShouldUpdate()) layer->OnImGuiUpdate(ts);
    }

    m_renderer->Flush();

    // FRAME END, reversed order
    for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it) {
      if ((*it)->ShouldUpdate()) (*it)->OnFrameEnd();
    }

    m_window->OnFrameEnd();
  }

  m_window->Destroy();
}

I_Window* Application::GetWindow()
{
  GL_ASSERT(m_window != nullptr, "No window available just yet");
  return m_window.get();
}

bool Application::IsVSync()
{
  return m_window->IsVSync();
}

void Application::SetVSync(bool val)
{
  m_window->SetVSync(val);
}

GLCore::Renderer2D* Application::GetRenderer()
{
  return m_renderer.get();
}

GLCore::LayerStack* Application::GetLayerStack()
{
  return &m_layerStack;
}

}  // namespace GLCore
