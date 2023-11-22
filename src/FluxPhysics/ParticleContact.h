#pragma once
#include <FluxPhysics/Particle.h>
#include <FluxPhysics/Utils/Vec.h>

namespace flux {
class ParticleContact {
 public:
  ParticleContact(Particle* particleA, Particle* particleB, float restitution, Vec3f normal);
  Particle* m_ParticleA;
  Particle* m_ParticleB;  // can be null

  float m_RestitutionCoefficient;
  Vec3f m_ContactNormal;

  float GetSeparatingVelocity() const;

 protected:
  void Resolve(float dt);
};
}  // namespace flux
