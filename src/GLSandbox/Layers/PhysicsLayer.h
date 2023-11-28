#pragma once
#include <GLCore/Core/Layer.h>

#include <GLSandbox/Utils/SandboxDebuggerAdapter.h>

#include <FluxPhysics/World.h>
#include <FluxPhysics/Particle.h>

#include <memory>

namespace GLSandbox
{
class PhysicsLayer : public GLCore::I_Layer
{
 public:
  PhysicsLayer() : I_Layer("Physics layer", true)
  {
  }

  void OnAttach() override;
  void OnDetach() override;

  void OnUpdate(GLCore::Timestep dt) override;

 private:
  void DebugDraw();

  std::unique_ptr<flux::World> m_World;
  SandboxDebuggerAdapter m_SandboxDebuggerAdapter;

  flux::Particle* m_ParticleA;
  flux::Particle* m_ParticleB;
  flux::Particle* m_ParticleC;
};
}  // namespace GLSandbox
