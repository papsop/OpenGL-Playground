#pragma once
#include <GLCore/Core/Layer.h>

#include <FluxPhysics/World.h>
#include <FluxPhysics/Particle.h>

#include <memory>

namespace GLSandbox {
class PhysicsLayer : public GLCore::I_Layer {
 public:
  PhysicsLayer() : I_Layer("Physics layer", true)
  {
  }

  void OnAttach() override;

  void OnUpdate(GLCore::Timestep dt) override;

 private:
  std::unique_ptr<flux::World> m_World;
  flux::Particle* m_Particle;
};
}  // namespace GLSandbox
