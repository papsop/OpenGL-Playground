#pragma once
#include <GLCore/Core/Window.h>
#include <GLFW/glfw3.h>
#include <GLAD/glad.h>

namespace GLCore {

class WindowsWindow : public I_Window {
 public:
  WindowsWindow() = default;
  ~WindowsWindow() override;

  void Update(Timestep ts) override;
  void Init(WindowDef def) override;
  void Destroy() override;

  uint32_t GetWidth() const override;
  uint32_t GetHeight() const override;

 private:
  GLFWwindow* m_window;
};
}  // namespace GLCore
