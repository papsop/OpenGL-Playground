#pragma once
#include <FluxPhysics/ParticleContact.h>
#include <FluxPhysics/ParticleLink.h>
#include <FluxPhysics/Utils/DebuggerAdapter.h>

#include <vector>
#include <memory>

namespace flux
{

class ParticleContactGenerator
{
 public:
  using T_Particles = std::vector<std::unique_ptr<Particle>>;
  using T_Contacts = std::vector<ParticleContact>;
  using T_ParticleLinks = std::vector<std::unique_ptr<ParticleLink>>;

  void GenerateContacts(T_Particles& particles, T_Contacts& contactsOutput);

 private:
  T_ParticleLinks m_ParticleLinks;
};

}  // namespace flux
