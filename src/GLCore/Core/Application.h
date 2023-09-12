#pragma once
#include <GLCore/Core/LayerStack.h>
#include <GLCore/Core/Window.h>

#include <memory>

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

  void Run();
  I_Window* GetWindow();

  bool IsVSync();
  void SetVSync(bool val);

 private:
  void Initialize();
  void InitGL();
  LayerStack* GetLayerStack();  // for AppControlOverlay

  inline static Application* m_instance = nullptr;
  bool m_isRunning = true;
  LayerStack m_layerStack;

  std::unique_ptr<I_Window> m_window = nullptr;

  friend class AppControlOverlay;
};
}  // namespace GLCore
