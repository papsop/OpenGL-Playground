#include <FluxPhysics/ForceGenerator.h>
#include <FluxPhysics/Particle.h>

namespace flux {

void GravityForceGenerator::UpdateForce(Particle* particle, float dt)
{
  particle->AddForce(m_Gravity * particle->GetMass());
}

}  // namespace flux
