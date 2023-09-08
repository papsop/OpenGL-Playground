#pragma once
#include <GLCore/Core/Timestep.h>

#include <cstdint>
#include <string>
namespace GLCore {
/*
 * Interface class for all the possible window types, platform specific implementations can be found in ../Platform/..
 */

struct WindowDef {
  std::string Title = "OpenGL_Playground";
  uint32_t Width = 1280;
  uint32_t Height = 720;
};

class I_Window {
 public:
  I_Window() = default;
  virtual ~I_Window() = default;

  virtual uint32_t GetWidth() const = 0;
  virtual uint32_t GetHeight() const = 0;

  virtual void OnFrameBegin() = 0;
  virtual void OnFrameEnd() = 0;
  virtual void Init(WindowDef def = WindowDef()) = 0;
  virtual void Destroy() = 0;

  virtual void* GetVoidWindow() = 0;

 private:
};
}  // namespace GLCore
