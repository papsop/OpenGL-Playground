#pragma once
#include <GLCore/Core/Layer.h>

#include <FluxPhysics/Particle.h>

namespace GLSandbox {
class PhysicsLayer : public GLCore::I_Layer {
 public:
  PhysicsLayer() : I_Layer("Physics layer", true)
  {
  }

  void OnAttach() override;

  void OnUpdate(GLCore::Timestep dt) override;

 private:
  flux::Particle m_Particle;
};
}  // namespace GLSandbox
