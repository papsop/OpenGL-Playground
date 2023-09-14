#pragma once
#include <GLCore/Core/Layer.h>

namespace GLSandbox {
class TestLayer : public GLCore::I_Layer {
 public:
  TestLayer() : I_Layer("Sandbox test layer")
  {
  }
  void OnUpdate(GLCore::Timestep dt) override;
};
}  // namespace GLSandbox
