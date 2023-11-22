#include <FluxPhysics/World.h>
#include <FluxPhysics/Particle.h>

#include <algorithm>
namespace flux
{

flux::Particle* World::CreateParticle()
{
  auto particle = std::unique_ptr<Particle>(new Particle(this));  // make_unique can't be used because of private constructor
  auto* result = particle.get();
  m_Particles.push_back(std::move(particle));
  return result;
}

void World::DestroyParticle(Particle* particle)
{
  auto predicate = [&](std::unique_ptr<Particle>& uqParticle) { return uqParticle.get() == particle; };

  m_Particles.erase(std::remove_if(m_Particles.begin(), m_Particles.end(), predicate), m_Particles.end());
}

void World::Step(float dt)
{
  for (auto& particle : m_Particles)
  {
    particle->Integrate(dt);
  }
}
}  // namespace flux
