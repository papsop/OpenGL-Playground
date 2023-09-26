#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Core/Events.h>

namespace GLSandbox {
class SandLayer : public GLCore::I_Layer {
 public:
  SandLayer() : I_Layer("Sand layer")
  {
  }

  void OnAttach() override;
  void OnDetach() override;

  void OnUpdate(GLCore::Timestep dt) override;
  void OnSandboxCanvasMouseEvent(const GLCore::E_SandboxCanvasMouseEvent& e);

 private:
};
}  // namespace GLSandbox
