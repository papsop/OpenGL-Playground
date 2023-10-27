#include <GLCore/Core/Application.h>
#include <GLCore/Core/Layer.h>
#include <GLCore/Core/Renderer.h>
#include <GLCore/Core/Events.h>

#include <GLCore/Layers/ImGuiOverlay.h>
#include <GLCore/Layers/ApplicationControlLayer.h>
#include <GLCore/Layers/SandboxCanvasLayer.h>
#include <GLCore/Layers/CameraControlLayer.h>
#include <GLCore/Layers/RendererControlLayer.h>

#include <GLCore/Utils/Camera.h>
#include <GLCore/Utils/OrthographicCamera.h>
#include <GLCore/Utils/PerspectiveCamera.h>
#include <GLCore/Utils/Log.h>
#include <GLCore/Utils/IDGenerator.h>

#include <GLCore/Platform/WindowsWindow.h>

#include <GLCore/Core/GLFWGlad.h>

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
  GL_ASSERT(m_instance != nullptr, "Application instance not yet initialized");
  return *m_instance;
}

void Application::PushLayer(I_Layer* layer)
{
  m_layerStack->PushLayer(layer);
}

void Application::PushOverlay(I_Layer* overlay)
{
  m_layerStack->PushOverlay(overlay);
}

void Application::Initialize()
{
  Log::Init();
  LOG_INFO("Initializing Application");
  m_layerStack = std::make_unique<LayerStack>();
  m_renderer = std::make_unique<Renderer2D>();
  m_sandboxCanvas = std::make_unique<SandboxCanvas>();
  m_eventDispatcher = std::make_unique<EventDispatcher>();

#ifdef _WINDOWS
  LOG_INFO("Creating a WindowsWindow");
  m_window = std::make_unique<WindowsWindow>();
  m_window->Init(/* default */);
#else
#error "Platform not supported"
#endif
  m_instance = this;
  LOG_INFO("Application initialized");
}

void Application::Run()
{
  m_renderer->Create();
  m_sandboxCanvas->Create();
  // Create camera AFTER canvas, so we can recalculate projection properly
  m_cameras[0] = std::unique_ptr<I_Camera>(new OrthographicCamera({10.0f, 10.0f}, {0.0f, 0.0f, 3.0f}));
  m_cameras[1] = std::unique_ptr<I_Camera>(new PerspectiveCamera({0.0f, 0.0f, 3.0f}));

  PushOverlay(new ImGuiOverlay());
  PushLayer(new SandboxCanvasLayer());
  PushLayer(new ApplicationControlLayer());
  PushLayer(new CameraControlLayer());
  PushLayer(new RendererControlLayer());

  REGISTER_EVENT_CALLBACK(E_WindowEvent, this, &Application::OnWindowEvent);

  SetActiveCameraIndex(1);  // perspective default for now

  float lastFrameTime = 0.0f;
  size_t frameCount = 0;

  while (m_isRunning) {
    frameCount++;
    float currentTime = static_cast<float>(glfwGetTime());
    Timestep ts = currentTime - lastFrameTime;
    lastFrameTime = currentTime;

    m_window->OnFrameBegin();

    // FRAME BEGIN
    for (auto* layer : *m_layerStack) {
      if (layer->ShouldUpdate()) layer->OnFrameBegin();
    }

    m_sandboxCanvas->Bind();
    // UPDATE
    for (auto* layer : *m_layerStack) {
      if (layer->ShouldUpdate()) layer->OnUpdate(ts);
    }
    m_renderer->Flush();
    m_sandboxCanvas->Unbind();

    // IMGUI UPDATE
    for (auto* layer : *m_layerStack) {
      if (layer->ShouldUpdate()) layer->OnImGuiUpdate(ts);
    }

    // FRAME END, reversed order
    for (auto it = (*m_layerStack).rbegin(); it != (*m_layerStack).rend(); ++it) {
      if ((*it)->ShouldUpdate()) (*it)->OnFrameEnd();
    }

    m_window->OnFrameEnd();

    m_eventDispatcher->ProcessAllEvents();
  }

  E_ApplicationEvent e;
  e.Type = E_ApplicationEvent::Close;
  DISPATCH_EVENT(e);

  UNREGISTER_EVENT_CALLBACK(E_WindowEvent, this);

  m_layerStack = nullptr;       // destroy
  m_eventDispatcher = nullptr;  // destroy
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

Renderer2D* Application::GetRenderer()
{
  GL_ASSERT(m_renderer != nullptr, "Renderer doesn't exist");
  return m_renderer.get();
}

SandboxCanvas* Application::GetSandboxCanvas()
{
  GL_ASSERT(m_sandboxCanvas != nullptr, "SandboxCanvas doesn't exist");
  return m_sandboxCanvas.get();
}

I_Camera* Application::GetMainCamera()
{
  GL_ASSERT(m_cameras[m_activeCameraIndex] != nullptr, "MainCamera doesn't exist");
  return m_cameras[m_activeCameraIndex].get();
}

EventDispatcher* Application::GetEventDispatcher()
{
  GL_ASSERT(m_eventDispatcher != nullptr, "EventDispatcher doesn't exist");
  return m_eventDispatcher.get();
}

void Application::SetActiveCameraIndex(int val)
{
  GL_TODO("Changing cameras should force canvas size update (inactive camera can get behind)");
  if (m_activeCameraIndex == val) return;  // imgui updated it every frame
  GL_TODO("Should Application really hold both cameras? Maybe let CameraControlLayer decide and just update application.");
  LOG_INFO("Switching cameras: {0} -> {1}", m_activeCameraIndex, val);
  m_activeCameraIndex = val;
}

int Application::GetActiveCameraIndex()
{
  return m_activeCameraIndex;
}

LayerStack* Application::GetLayerStack()
{
  return m_layerStack.get();
}

}  // namespace GLCore
