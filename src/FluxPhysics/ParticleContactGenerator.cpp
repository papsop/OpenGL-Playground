#include <FluxPhysics/ParticleContactGenerator.h>
#include <FluxPhysics/Particle.h>

#include <iostream>
namespace flux
{
void ParticleContactGenerator::GenerateContacts(T_Particles& particles, T_Contacts& contactsOutput)
{
  for (size_t i = 0; i < particles.size(); i++)
  {
    for (size_t j = i + 1; j < particles.size(); j++)
    {
      Particle* particleA = particles[i].get();
      Particle* particleB = particles[j].get();

      float distance = (particleB->GetPosition() - particleA->GetPosition()).lengthSquared();
      distance -= particleA->GetRadius() * particleA->GetRadius();
      distance -= particleB->GetRadius() * particleB->GetRadius();
      if (distance <= 0)
      {
        Vec3f dir = particleA->GetPosition() - particleB->GetPosition();
        dir.normalize();
        contactsOutput.push_back({particleA, particleB, 1.0f, dir});
      }
    }
  }
}
}  // namespace flux
