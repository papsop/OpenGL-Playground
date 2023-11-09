#pragma once
#include <GLCore/Core/Layer.h>

namespace GLSandbox {
class PhysicsLayer : public GLCore::I_Layer {
 public:
  PhysicsLayer() : I_Layer("Physics layer", true)
  {
  }
};
}  // namespace GLSandbox
