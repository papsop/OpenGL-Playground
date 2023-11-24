#include <FluxPhysics/ParticleContactGenerator.h>
#include <FluxPhysics/Particle.h>

#include <iostream>
namespace flux
{
void ParticleContactGenerator::GenerateContacts(const T_Particles& particles, T_Contact& contactsOutput)
{
  for (size_t i = 0; i < particles.size(); i++)
  {
    for (size_t j = i + 1; j < particles.size(); j++)
    {
      const Particle* particleA = particles[i].get();
      const Particle* particleB = particles[j].get();

      float distance = (particleB->GetPosition() - particleA->GetPosition()).length();
      distance -= particleA->GetRadius();
      distance -= particleB->GetRadius();
      if (distance <= 0)
      {
        std::cout << "contact" << std::endl;
      }
    }
  }
}
}  // namespace flux
