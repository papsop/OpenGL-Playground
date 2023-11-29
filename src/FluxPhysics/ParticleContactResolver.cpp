#include <FluxPhysics/ParticleContactResolver.h>

namespace flux
{

void ParticleContactResolver::ResolveContacts(T_Contact& contacts, float dt)
{
  for (auto& contact : contacts)
  {
    contact.Resolve(dt);
  }
}

}  // namespace flux
