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
  using T_Contact = std::vector<ParticleContact>;

  void GenerateContacts(const T_Particles& particles, T_Contact& contactsOutput);

 private:
};
}  // namespace flux
