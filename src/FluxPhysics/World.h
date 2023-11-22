#pragma once

#include <vector>
#include <memory>

namespace flux
{
class Particle;

class World
{
 public:
  Particle* CreateParticle();
  // TODO: support deletion by ID?
  void DestroyParticle(Particle* particle);

  void Step(float dt);

 private:
  std::vector<std::unique_ptr<Particle>> m_Particles;
};
}  // namespace flux
