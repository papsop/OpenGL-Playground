#pragma once
#include <GLCore/Core/Layer.h>

namespace GLCore {

class SandboxCanvas;
class SandboxCanvasLayer : public I_Layer {
 public:
  SandboxCanvasLayer() : I_Layer("Sandbox canvas", true, true)
  {
  }
  void OnAttach() override;
  void OnDetach() override;
  void OnImGuiUpdate(Timestep dt) override;

 private:
  void HandleCanvasMouseEvents();
  SandboxCanvas* m_sandboxCanvas;
};
}  // namespace GLCore
