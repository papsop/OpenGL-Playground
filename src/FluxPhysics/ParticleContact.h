#pragma once
#include <FluxPhysics/Utils/Vec.h>

namespace flux
{
class Particle;
class ParticleContactResolver;
class ParticleContact
{
 public:
  ParticleContact(Particle* particleA, Particle* particleB, float restitution, Vec3f normal, float penetration);
  Particle* m_ParticleA;
  Particle* m_ParticleB;  // can be null

  float m_RestitutionCoefficient;
  Vec3f m_ContactNormal;
  float m_Penetration;

  float GetSeparatingVelocity() const;

 protected:
  void Resolve(float dt);

  void ResolveVelocity(float dt);
  void ResolveInterpenetration(float dt);

  friend class ParticleContactResolver;
};
}  // namespace flux
