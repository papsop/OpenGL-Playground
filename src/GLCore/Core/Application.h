#pragma once
#include <GLCore/Core/LayerStack.h>
#include <GLCore/Core/Window.h>
#include <GLCore/Core/Renderer.h>
#include <GLCore/Core/SandboxCanvas.h>
#include <GLCore/Core/Events.h>
#include <GLCore/Utils/Camera.h>

#include <memory>
#include <iostream>
namespace GLCore {
class ApplicationControlLayer;
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
  I_Camera* GetMainCamera();
  EventDispatcher* GetEventDispatcher();

  void OnWindowEvent(const E_WindowEvent& event);

  void SetActiveCameraIndex(int val);
  int GetActiveCameraIndex();

 private:
  void Initialize();
  LayerStack* GetLayerStack();  // for AppControlOverlay

  inline static Application* m_instance = nullptr;
  bool m_isRunning = true;
  int m_activeCameraIndex = 0;
  std::unique_ptr<LayerStack> m_layerStack;
  std::unique_ptr<Renderer2D> m_renderer;
  std::unique_ptr<SandboxCanvas> m_sandboxCanvas;
  GL_TODO("Refactor cameras")
  std::array<std::unique_ptr<I_Camera>, 2> m_cameras;

  std::unique_ptr<I_Window> m_window = nullptr;

  std::unique_ptr<EventDispatcher> m_eventDispatcher;

  friend class ApplicationControlLayer;
};
}  // namespace GLCore
