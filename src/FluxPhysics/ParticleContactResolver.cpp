#include <FluxPhysics/ParticleContactResolver.h>

namespace flux
{

// =======================================================================
void ParticleContactResolver::ResolveContacts(T_Contact& contacts, float dt)
{
  for (auto& contact : contacts)
  {
    contact.Resolve(dt);
  }

  // Separating velocity is >0 for some contacts and this way they won't get resolved
  // TODO: implement iterations like this later, cba right now
  // =====

  // size_t maxIterations = contacts.size() * 2;
  // size_t iterationsUsed = 0;

  // while (iterationsUsed < maxIterations)
  //{
  //   float max = 0;
  //   ParticleContact* maxContact = nullptr;

  //  for (auto& contact : contacts)
  //  {
  //    float sepVelocity = contact.GetSeparatingVelocity();
  //    std::cout << sepVelocity << std::endl;
  //    if (sepVelocity < max)
  //    {
  //      max = sepVelocity;
  //      maxContact = &contact;
  //    }
  //  }
  //  if (maxContact)
  //  {
  //    maxContact->Resolve(dt);
  //  }

  //  iterationsUsed++;
  //}
}

}  // namespace flux
