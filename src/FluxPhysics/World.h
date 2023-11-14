#pragma once
#include <FluxPhysics/Particle.h>

#include <vector>
#include <memory>

namespace flux {
class World {
 public:
  Particle* CreateParticle();

  void Step(float dt);

 private:
  std::vector<std::unique_ptr<Particle>> m_Particles;
};
}  // namespace flux
