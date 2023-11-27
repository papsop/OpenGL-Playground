#pragma once
#include <FluxPhysics/ParticleContactGenerator.h>
#include <FluxPhysics/ParticleContactResolver.h>

#include <vector>
#include <memory>

namespace flux
{
class Particle;
class I_DebuggerAdapter;

class World
{
 public:
  Particle* CreateParticle();
  // TODO: support deletion by ID?
  void DestroyParticle(Particle* particle);

  void Step(float dt);
  void DebugDraw();

  void ConnectDebugger(I_DebuggerAdapter* debugger);
  void DisconnectDebugger();

 private:
  std::vector<std::unique_ptr<Particle>> m_Particles;

  ParticleContactGenerator m_ContactGenerator;
  ParticleContactResolver m_ContactResolver;
  I_DebuggerAdapter* m_Debugger;
};
}  // namespace flux
