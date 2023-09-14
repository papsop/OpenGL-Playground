#pragma once
#include <GLCore/Core/Layer.h>

namespace GLCore {

class SandboxCanvas;
class SandboxCanvasOverlay : public I_Layer {
 public:
  SandboxCanvasOverlay() : I_Layer("Sandbox canvas", true)
  {
  }
  void OnAttach() override;
  void OnDetach() override;
  void OnImGuiUpdate(Timestep dt) override;

 private:
  SandboxCanvas* m_sandboxCanvas;
};
}  // namespace GLCore
