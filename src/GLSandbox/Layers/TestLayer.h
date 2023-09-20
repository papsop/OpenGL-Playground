#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Core/Events.h>

namespace GLSandbox {
class TestLayer : public GLCore::I_Layer {
 public:
  TestLayer() : I_Layer("Sandbox test layer")
  {
  }

  void OnAttach() override;
  void OnDetach() override;

  void OnUpdate(GLCore::Timestep dt) override;
  void OnMouseInputEvent(const GLCore::MouseInputEvent& e);
};
}  // namespace GLSandbox
