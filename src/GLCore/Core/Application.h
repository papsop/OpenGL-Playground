#pragma once
#include <GLCore/Core/LayerStack.h>
#include <GLCore/Core/Window.h>

#include <memory>

namespace GLCore {
class ImGuiOverlay;
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

 private:
  void Initialize();
  void InitGL();

  inline static Application* m_instance = nullptr;
  bool m_isRunning = true;
  LayerStack m_layerStack;
  ImGuiOverlay* m_imGuiOverlay = nullptr;
  std::unique_ptr<I_Window> m_window = nullptr;
};
}  // namespace GLCore
