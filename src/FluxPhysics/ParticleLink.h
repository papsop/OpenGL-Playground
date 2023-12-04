#pragma once
#include <FluxPhysics/Utils/Vec.h>
#include <FluxPhysics/Utils/DebuggerAdapter.h>

#include <vector>
namespace flux
{

class Particle;
class ParticleContact;

class ParticleLink : public I_Debuggable
{
 public:
  using T_Contacts = std::vector<ParticleContact>;

  ParticleLink(Particle* particleA, Particle* particleB, Vec4f color);

  virtual void GenerateContactForLink(T_Contacts& contacts) = 0;
  virtual void DebugDraw(I_DebuggerAdapter* debugger) override;

  float GetLength() const;

  Particle* m_ParticleA;
  Particle* m_ParticleB;

  Vec4f m_Color;  // for debug draws
};

// =======================================================================
class ParticleCable : public ParticleLink
{
 public:
  ParticleCable(Particle* particleA, Particle* particleB, float maxLength, float restitution);

  void GenerateContactForLink(T_Contacts& contacts) override;

  float m_Restitution;
  float m_MaxLength;
};

// =======================================================================
class ParticleRod : public ParticleLink
{
 public:
  ParticleRod(Particle* particleA, Particle* particleB, float maxLength);

  void GenerateContactForLink(T_Contacts& contacts) override;

  float m_MaxLength;
};

}  // namespace flux
