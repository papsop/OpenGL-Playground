#include <FluxPhysics/ParticleContactGenerator.h>
#include <FluxPhysics/Particle.h>

#include <iostream>
#include <cmath>
namespace flux
{

// =======================================================================
void ParticleContactGenerator::GenerateContacts(T_Particles& particles, T_Contacts& contactsOutput)
{
  // Particle collisions
  for (size_t i = 0; i < particles.size(); i++)
  {
    for (size_t j = i + 1; j < particles.size(); j++)
    {
      Particle* particleA = particles[i].get();
      Particle* particleB = particles[j].get();

      if (particleA->GetInverseMass() == 0 && particleB->GetInverseMass() == 0) continue;  // 2 immovable objects

      // use length squared and ignore sqrt? not relevant right now
      float distance = (particleB->GetPosition() - particleA->GetPosition()).length();
      distance -= particleA->GetRadius();
      distance -= particleB->GetRadius();
      if (distance <= 0)
      {
        Vec3f contactNormal = (particleA->GetPosition() - particleB->GetPosition()).normalize();
        float penetration = std::abs(distance);
        contactsOutput.push_back({particleA, particleB, .95f, contactNormal, penetration});
      }
    }
  }

  // Particle links
  for (auto& particleLink : m_ParticleLinks)
  {
    particleLink->GenerateContactForLink(contactsOutput);
  }
}

// =======================================================================
void ParticleContactGenerator::AddParticleLink(ParticleLink* particleLink)
{
  m_ParticleLinks.push_back(std::unique_ptr<ParticleLink>(particleLink));
}

// =======================================================================
ParticleContactGenerator::T_ParticleLinks& ParticleContactGenerator::GetParticleLinks()
{
  return m_ParticleLinks;
}

}  // namespace flux
