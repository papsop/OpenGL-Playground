#include <FluxPhysics/ParticleContactResolver.h>

namespace flux
{

void ParticleContactResolver::ResolveContacts(T_Contact& contacts, float dt)
{
  for (auto& contact : contacts)
  {
    auto separatingVelocity = contact.GetSeparatingVelocity();
    contact.Resolve(dt);
  }
}

}  // namespace flux
