#pragma once
#include <FluxPhysics/Particle.h>
#include <FluxPhysics/ForceGenerator.h>

#include <vector>
#include <memory>

namespace flux {
class World {
 public:
  Particle* CreateParticle();
  void DestroyParticle(Particle* particle);

  // void AddForceGenerator(ForceGenerator* fg);
  void RegisterForceGenerator(ForceGenerator* fg, Particle* particle);

  void Step(float dt);

 private:
  struct ForceGeneratorEntry {
    ForceGenerator* forceGenerator;
    Particle* particle;
  };

  std::vector<std::unique_ptr<Particle>> m_Particles;
  std::vector<ForceGeneratorEntry> m_ForceGeneratorEntries;
};
}  // namespace flux
