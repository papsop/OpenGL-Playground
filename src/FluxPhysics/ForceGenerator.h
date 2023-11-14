#pragma once

namespace flux {
class Particle;

class ForceGenerator {
 public:
  virtual void UpdateForce(Particle* particle, float dt) = 0;
};
}  // namespace flux
