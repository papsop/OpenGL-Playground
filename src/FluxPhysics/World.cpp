#include <FluxPhysics/World.h>

namespace flux {

flux::Particle* World::CreateParticle()
{
  auto particle = std::unique_ptr<Particle>(new Particle(this));  // make_unique can't be used because of private constructor
  auto* result = particle.get();
  m_Particles.push_back(std::move(particle));
  return result;
}

void World::RegisterForceGenerator(ForceGenerator* fg, Particle* particle)
{
  ForceGeneratorEntry entry;
  entry.forceGenerator = fg;
  entry.particle = particle;
  m_ForceGeneratorEntries.push_back(entry);
}

void World::Step(float dt)
{
  for (auto& entry : m_ForceGeneratorEntries) {
    entry.forceGenerator->UpdateForce(entry.particle, dt);
  }

  for (auto& particle : m_Particles) {
    particle->Integrate(dt);
  }
}
}  // namespace flux
