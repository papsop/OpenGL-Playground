#pragma once
#include <FluxPhysics/ParticleContact.h>

#include <vector>
#include <memory>

namespace flux
{
class ParticleContactGenerator
{
 public:
  using T_Particles = std::vector<std::unique_ptr<Particle>>;
  using T_Contacts = std::vector<ParticleContact>;

  void GenerateContacts(T_Particles& particles, T_Contacts& contactsOutput);

 private:
};
}  // namespace flux
