#include <FluxPhysics/ParticleContactResolver.h>

namespace flux
{

// =======================================================================
void ParticleContactResolver::ResolveContacts(T_Contact& contacts, float dt)
{
  if (contacts.size() == 0) return;

  // for (auto& contact : contacts)
  //{
  //   contact.Resolve(dt);
  // }

  // The lowest separating velocity means the stronger collision, solve them first
  size_t maxIterations = contacts.size() * 2;
  size_t iterationsUsed = 0;

  while (iterationsUsed < maxIterations)
  {
    float max = 0;
    ParticleContact* maxContact = nullptr;

    for (auto& contact : contacts)
    {
      float sepVelocity = contact.GetSeparatingVelocity();
      if (sepVelocity < max)
      {
        max = sepVelocity;
        maxContact = &contact;
      }
    }
    if (maxContact)
    {
      maxContact->Resolve(dt);
    }

    iterationsUsed++;
  }
}

}  // namespace flux
