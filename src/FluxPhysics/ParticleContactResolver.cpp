#include <FluxPhysics/ParticleContactResolver.h>

namespace flux
{

// =======================================================================
void ParticleContactResolver::ResolveContacts(T_Contact& contacts, float dt)
{
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
