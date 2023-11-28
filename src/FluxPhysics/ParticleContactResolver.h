#pragma once
#include <FluxPhysics/ParticleContact.h>

#include <vector>

namespace flux
{

class ParticleContactResolver
{
 public:
  using T_Contact = std::vector<ParticleContact>;

  void ResolveContacts(T_Contact& contacts, float dt);
};

}  // namespace flux
