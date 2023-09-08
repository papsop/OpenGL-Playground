#pragma once
#include <GLCore/Core/Window.h>
#include <GLFW/glfw3.h>
#include <GLAD/glad.h>

namespace GLCore {

class WindowsWindow : public I_Window {
 public:
  WindowsWindow() = default;
  ~WindowsWindow() override;

  void Destroy() override;

  uint32_t GetWidth() const override;
  uint32_t GetHeight() const override;

  void Init(WindowDef def = WindowDef()) override;
  void* GetVoidWindow() override;

  void OnFrameBegin() override;
  void OnFrameEnd() override;

 private:
  GLFWwindow* m_window;
};
}  // namespace GLCore
