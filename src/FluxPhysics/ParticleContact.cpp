#include <FluxPhysics/ParticleContact.h>
#include <FluxPhysics/Particle.h>

namespace flux
{

ParticleContact::ParticleContact(Particle* particleA, Particle* particleB, float restitution, Vec3f normal, float penetration)
    : m_ParticleA(particleA), m_ParticleB(particleB), m_RestitutionCoefficient(restitution), m_ContactNormal(normal), m_Penetration(penetration)
{
}

float ParticleContact::GetSeparatingVelocity() const
{
  Vec3f relativeVelocity = m_ParticleA->GetVelocity();
  if (m_ParticleB) relativeVelocity -= m_ParticleB->GetVelocity();
  return relativeVelocity.dot(m_ContactNormal);
}

void ParticleContact::Resolve(float dt)
{
  float separatingVelocity = GetSeparatingVelocity();

  if (separatingVelocity > 0)
  {
    return;
  }

  float newVelocity = -separatingVelocity * m_RestitutionCoefficient;
  float deltaVelocity = newVelocity - separatingVelocity;

  // apply change in velocity based on particle's inverse mass
  // that way more massive objects will move less and lighter will move more
  float totalInverseMass = m_ParticleA->GetInverseMass();
  if (m_ParticleB) totalInverseMass += m_ParticleB->GetInverseMass();

  if (totalInverseMass <= 0)
  {
    return;
  }

  float impulse = deltaVelocity / totalInverseMass;
  Vec3f impulsePerInverseMass = m_ContactNormal * impulse;

  // apply impulses
  m_ParticleA->AddVelocity(impulsePerInverseMass * m_ParticleA->GetInverseMass());
  if (m_ParticleB)
  {
    m_ParticleB->AddVelocity(impulsePerInverseMass * -m_ParticleB->GetInverseMass());
  }
}
}  // namespace flux
