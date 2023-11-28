#include <FluxPhysics/World.h>
#include <FluxPhysics/Particle.h>
#include <FluxPhysics/ParticleContact.h>
#include <FluxPhysics/Utils/DebuggerAdapter.h>

#include <algorithm>
namespace flux
{

// =======================================================================
flux::Particle* World::CreateParticle()
{
  auto particle = std::unique_ptr<Particle>(new Particle(this));  // make_unique can't be used because of private constructor
  auto* result = particle.get();
  m_Particles.push_back(std::move(particle));
  return result;
}

// =======================================================================
void World::DestroyParticle(Particle* particle)
{
  auto predicate = [&](std::unique_ptr<Particle>& uqParticle) { return uqParticle.get() == particle; };

  m_Particles.erase(std::remove_if(m_Particles.begin(), m_Particles.end(), predicate), m_Particles.end());
}

// =======================================================================

void World::ConnectDebugger(I_DebuggerAdapter* debugger)
{
  m_Debugger = debugger;
}

// =======================================================================
void World::DisconnectDebugger()
{
  m_Debugger = nullptr;
}

// =======================================================================
void World::SetGravity(Vec3f gravity)
{
  m_Gravity = gravity;
}

// =======================================================================
void World::Step(float dt)
{
  // 1. Apply gravity to particles
  for (auto& particle : m_Particles)
  {
    if (particle->IsGravityEnabled())
    {
      particle->AddForce(m_Gravity * particle->GetMass());
    }
  }

  // 2. Update particle positions/velocities
  for (auto& particle : m_Particles)
  {
    particle->Integrate(dt);
  }

  // 3. Generate contacts between new particle positions
  std::vector<ParticleContact> contacts;
  m_ContactGenerator.GenerateContacts(m_Particles, contacts);

  // 4. Solve these contacts and apply corresponding impulses to the particles
  if (contacts.size() > 0)
  {
    m_ContactResolver.ResolveContacts(contacts, dt);
  }
}
// =======================================================================
void World::DebugDraw()
{
  if (!m_Debugger) return;

  for (const auto& particle : m_Particles)
  {
    // Collider
    if (m_Debugger->ShouldDrawBody())
    {
      m_Debugger->DrawCircle(particle->GetPosition(), particle->GetRadius(), {1.0f});
    }

    // Velocity direction
    if (m_Debugger->ShouldDrawDirection())
    {
      Vec3f velocityDirection = particle->GetPosition() + (particle->GetVelocity().normalize() / 2.0f);
      m_Debugger->DrawLine(particle->GetPosition(), velocityDirection, {1.0f, 0.0f, 0.0f, 1.0f});
    }
  }
}

}  // namespace flux
