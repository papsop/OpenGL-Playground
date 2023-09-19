#pragma once
#include <GLCore/Core/LayerStack.h>
#include <GLCore/Core/Window.h>
#include <GLCore/Core/Renderer.h>
#include <GLCore/Core/SandboxCanvas.h>
#include <GLCore/Core/Events.h>
#include <GLCore/Utils/OrtographicCamera.h>

#include <memory>
#include <iostream>
namespace GLCore {
class AppControlOverlay;
/*
 *	A singleton object that takes care of the window/input handling and holds all the layers.
 */
class Application {
 public:
  Application();
  ~Application();
  static Application& Instance();

  void PushLayer(I_Layer* layer);
  void PushOverlay(I_Layer* overlay);

  void Run();

  bool IsVSync();
  void SetVSync(bool val);

  I_Window* GetWindow();
  Renderer2D* GetRenderer();
  SandboxCanvas* GetSandboxCanvas();
  OrthographicCamera* GetMainCamera();
  EventDispatcher* GetEventDispatcher();

  void OnWindowEvent(const WindowEvent& event)
  {
    if (event.Type == WindowEvent::Close) {
      m_isRunning = false;
    }
  }

 private:
  void Initialize();
  void InitGL();
  LayerStack* GetLayerStack();  // for AppControlOverlay

  inline static Application* m_instance = nullptr;
  bool m_isRunning = true;
  LayerStack m_layerStack;
  std::unique_ptr<Renderer2D> m_renderer;
  std::unique_ptr<SandboxCanvas> m_sandboxCanvas;
  std::unique_ptr<OrthographicCamera> m_orthoCamera;

  std::unique_ptr<I_Window> m_window = nullptr;

  std::unique_ptr<EventDispatcher> m_eventDispatcher;

  friend class AppControlOverlay;
};
}  // namespace GLCore
