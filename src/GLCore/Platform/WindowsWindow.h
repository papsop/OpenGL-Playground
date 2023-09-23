#pragma once
#include <GLCore/Core/Window.h>
#include <GLCore/Core/GLFWGlad.h>

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

  bool IsVSync() override;
  void SetVSync(bool val) override;

  void OnWindowCloseCallback(GLFWwindow* window);

 private:
  GLFWwindow* m_window;
  bool m_vSyncEnabled = true;
};
}  // namespace GLCore
