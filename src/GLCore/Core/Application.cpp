#include <GLCore/Core/Application.h>
#include <GLCore/Core/Layer.h>
#include <GLCore/Core/Renderer.h>

#include <GLCore/Layers/ImGuiOverlay.h>
#include <GLCore/Layers/AppControlOverlay.h>
#include <GLCore/Layers/SandboxCanvasOverlay.h>
#include <GLCore/Layers/CameraControlOverlay.h>

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

  m_sandboxCanvas->Destroy();
  m_sandboxCanvas = nullptr;
}

Application& Application::Instance()
{
  return *m_instance;
}

void Application::PushLayer(I_Layer* layer)
{
  m_layerStack.PushLayer(layer);
}

void Application::PushOverlay(I_Layer* overlay)
{
  m_layerStack.PushOverlay(overlay);
}

void Application::Initialize()
{
  Log::Init();
  LOG_INFO("Initializing Application");
  InitGL();
  m_renderer = std::make_unique<Renderer2D>();
  m_sandboxCanvas = std::make_unique<SandboxCanvas>();
  m_orthoCamera = std::make_unique<OrthographicCamera>(-5.0f, 5.0f, -5.0f, 5.0f);
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
  m_sandboxCanvas->Create();

  PushOverlay(new ImGuiOverlay());
  PushOverlay(new AppControlOverlay());
  PushOverlay(new SandboxCanvasOverlay());
  PushOverlay(new CameraControlOverlay());

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

    m_sandboxCanvas->Bind();
    // UPDATE
    for (auto* layer : m_layerStack) {
      if (layer->ShouldUpdate()) layer->OnUpdate(ts);
    }
    m_renderer->Flush();
    m_sandboxCanvas->Unbind();

    // IMGUI UPDATE
    for (auto* layer : m_layerStack) {
      if (layer->ShouldUpdate()) layer->OnImGuiUpdate(ts);
    }

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

GLCore::SandboxCanvas* Application::GetSandboxCanvas()
{
  return m_sandboxCanvas.get();
}

GLCore::OrthographicCamera* Application::GetMainCamera()
{
  return m_orthoCamera.get();
}

GLCore::LayerStack* Application::GetLayerStack()
{
  return &m_layerStack;
}

}  // namespace GLCore
