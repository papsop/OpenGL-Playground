#pragma once
#include <FluxPhysics/Utils/Vec.h>

namespace flux {
class Particle;

struct ForceGenerator {
 public:
  virtual void UpdateForce(Particle* particle, float dt) = 0;
};

class GravityForceGenerator : public ForceGenerator {
 public:
  virtual void UpdateForce(Particle* particle, float dt);

 private:
  Vec3f m_Gravity = {0, -10, 0};
};
}  // namespace flux
