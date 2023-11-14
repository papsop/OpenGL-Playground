#include <FluxPhysics/Particle.h>

namespace flux {

Particle::Particle(World* world) : m_World(world)
{
}

void Particle::SetMass(float mass)
{
  m_Mass = mass;
  m_InverseMass = 1.0f / m_Mass;
}

void Particle::SetDamping(float damp)
{
  m_Damping = damp;
}

void Particle::SetAcceleration(Vec3f acceleration)
{
  m_Acceleration = acceleration;
}

void Particle::SetVelocity(Vec3f velocity)
{
  m_Velocity = velocity;
}

flux::Vec3f Particle::GetPosition() const
{
  return m_Position;
}

flux::Vec3f Particle::GetVelocity() const
{
  return m_Velocity;
}

flux::Vec3f Particle::GetAcceleration() const
{
  return m_Acceleration;
}

float Particle::GetMass() const
{
  return m_Mass;
}

void Particle::AddForce(Vec3f force)
{
  m_ForceAccumulator += force;
}

void Particle::Integrate(float dt)
{
  // position update
  m_Position += m_Velocity * dt;

  // acceleration update
  Vec3f resultAcceleration = m_Acceleration + m_ForceAccumulator * dt;

  // velocity update
  m_Velocity += resultAcceleration * dt;
  m_Velocity *= powf(m_Damping, dt);

  m_ForceAccumulator.clear();
}

}  // namespace flux
