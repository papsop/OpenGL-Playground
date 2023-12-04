#include <FluxPhysics/ParticleLink.h>
#include <FluxPhysics/Particle.h>
#include <FluxPhysics/ParticleContact.h>

namespace flux
{

ParticleLink::ParticleLink(Particle* particleA, Particle* particleB, Vec4f color) : m_ParticleA(particleA), m_ParticleB(particleB), m_Color(color)
{
}

// =======================================================================
void ParticleLink::DebugDraw(I_DebuggerAdapter* debugger)
{
  if (!debugger) return;

  debugger->DrawLine(m_ParticleA->GetPosition(), m_ParticleB->GetPosition(), m_Color);
}

// =======================================================================
float ParticleLink::GetLength() const
{
  Vec3f dir = m_ParticleA->GetPosition() - m_ParticleB->GetPosition();
  return dir.length();
}

// =======================================================================
ParticleCable::ParticleCable(Particle* particleA, Particle* particleB, float maxLength, float restitution)
    : ParticleLink(particleA, particleB, {1.0f, 1.0f, 0.0f, 1.0f}), m_MaxLength(maxLength), m_Restitution(restitution)
{
}

// =======================================================================
void ParticleCable::GenerateContactForLink(T_Contacts& contacts)
{
  float length = GetLength();

  if (length < m_MaxLength)
  {
    return;
  }

  Vec3f contactNormal = m_ParticleB->GetPosition() - m_ParticleA->GetPosition();
  contactNormal.normalize();

  float penetration = length - m_MaxLength;

  contacts.push_back({m_ParticleA, m_ParticleB, m_Restitution, contactNormal, penetration});
}

// =======================================================================
ParticleRod::ParticleRod(Particle* particleA, Particle* particleB, float maxLength)
    : ParticleLink(particleA, particleB, {0.0f, 1.0f, 1.0f, 1.0f}), m_MaxLength(maxLength)
{
}

// =======================================================================
void ParticleRod::GenerateContactForLink(T_Contacts& contacts)
{
  // TODO: rods don't work without iterations, need to fix somehow
  float length = GetLength();

  if (length == m_MaxLength)
  {
    return;
  }

  Vec3f contactNormal = m_ParticleB->GetPosition() - m_ParticleA->GetPosition();
  contactNormal.normalize();

  float penetration = 0.0f;

  if (length > m_MaxLength)
  {
    penetration = length - m_MaxLength;
  }
  else
  {
    contactNormal = -contactNormal;
    penetration = m_MaxLength - length;
  }

  contacts.push_back({m_ParticleA, m_ParticleB, 0.0f, contactNormal, penetration});
  // contacts.push_back({m_ParticleB, m_ParticleA, 0.0f, contactNormal, penetration});
}

}  // namespace flux
