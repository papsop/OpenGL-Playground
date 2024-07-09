#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Core/Events.h>

#include <GLSandbox/Utils/SandboxDebuggerAdapter.h>

#include <FluxPhysics/World.h>
#include <FluxPhysics/Particle.h>

#include <memory>

namespace GLSandbox
{
class PhysicsLayer : public GLCore::I_Layer
{
 public:
  PhysicsLayer(bool enabled) : I_Layer("Physics layer", enabled)
  {
  }

  void OnAttach() override;
  void OnDetach() override;

  void OnUpdate(GLCore::Timestep dt) override;

  void OnSandboxCanvasMouseEvent(const GLCore::E_SandboxCanvasMouseEvent& e);

  void OnImGuiUpdate(GLCore::Timestep dt) override;

 private:
  void DebugDraw();

  std::unique_ptr<flux::World> m_World;
  SandboxDebuggerAdapter m_SandboxDebuggerAdapter;

  flux::Particle* m_ParticleWallA;
  flux::Particle* m_ParticleWallB;
  flux::Particle* m_ParticleWallC;

  std::vector<flux::Particle*> m_Balls;

  float m_UpdateAccumulator;
  float m_FixedUpdate = 1.0f / 60.0f;
};
}  // namespace GLSandbox
