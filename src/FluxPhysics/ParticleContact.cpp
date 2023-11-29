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
  ResolveVelocity(dt);
  ResolveInterpenetration(dt);
}

void ParticleContact::ResolveVelocity(float dt)
{
  float separatingVelocity = GetSeparatingVelocity();

  if (separatingVelocity > 0)
  {
    return;
  }

  float newVelocity = -separatingVelocity * m_RestitutionCoefficient;

  // Velocity build-up due to acceleration only
  Vec3f velocityBuildup = m_ParticleA->GetAcceleration();
  if (m_ParticleB) velocityBuildup -= m_ParticleB->GetAcceleration();
  // Velocity in the direction of contact normal
  float accelerationSeparationVelocity = velocityBuildup.dot(m_ContactNormal) * dt;

  if (accelerationSeparationVelocity < 0)
  {  // if there is such velocity, remove it from new separating velocity
    newVelocity += m_RestitutionCoefficient * accelerationSeparationVelocity;
    newVelocity = std::max(newVelocity, 0.0f);
  }

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

void ParticleContact::ResolveInterpenetration(float dt)
{
  if (m_Penetration <= 0) return;

  float totalInverseMass = m_ParticleA->GetInverseMass();
  if (m_ParticleB) totalInverseMass += m_ParticleB->GetInverseMass();

  if (totalInverseMass <= 0) return;

  Vec3f movePerInverseMass = (m_ContactNormal * m_Penetration) / totalInverseMass;

  m_ParticleA->SetPosition(m_ParticleA->GetPosition() + movePerInverseMass * m_ParticleA->GetInverseMass());
  if (m_ParticleB)
  {
    m_ParticleB->SetPosition(m_ParticleB->GetPosition() - movePerInverseMass * m_ParticleB->GetInverseMass());
  }
}
}  // namespace flux
