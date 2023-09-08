#pragma once
#include <GLCore/Core/LayerStack.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace GLCore
{
class ImGuiOverlay;
/*
 *	A singleton object that takes care of the window/input handling and holds all the layers.
 */
class Application
{
 public:
  Application();
  ~Application();
  static Application& Instance();

  void Run();
  static void window_close_callback(GLFWwindow* window);

  GLFWwindow* GetWindow();

 private:
  void Initialize();
  void InitGL();

  inline static Application* m_instance = nullptr;
  inline static bool m_isRunning = true;
  GLFWwindow* m_window = nullptr;
  LayerStack m_layerStack;
  ImGuiOverlay* m_imGuiOverlay = nullptr;
};
}  // namespace GLCore
