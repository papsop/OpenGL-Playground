#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace GLCore {
/*
 *	A singleton object that takes care of the window/input handling and holds all the layers.
 */
class Application {
 public:
  Application();
  ~Application();
  static Application& Instance();

 private:
  void InitGL();

  inline static Application* m_instance = nullptr;
  GLFWwindow* m_window = nullptr;
};
}  // namespace GLCore
