#include <FluxPhysics/Particle.h>
#include <FluxPhysics/World.h>

namespace flux
{

// =======================================================================
Particle::Particle(World* world) : m_World(world)
{
}

// =======================================================================
void Particle::Destroy()
{
  if (m_World)
  {
    m_World->DestroyParticle(this);
  }
}

// =======================================================================
void Particle::SetPosition(Vec3f position)
{
  m_Position = position;
}

// =======================================================================
void Particle::SetMass(float mass)
{
  m_Mass = mass;
  m_InverseMass = (mass > 0.0f) ? 1.0f / m_Mass : 0.0f;
}

// =======================================================================
void Particle::SetDamping(float damp)
{
  m_Damping = damp;
}

// =======================================================================
void Particle::SetAcceleration(Vec3f acceleration)
{
  m_Acceleration = acceleration;
}

// =======================================================================
void Particle::SetVelocity(Vec3f velocity)
{
  m_Velocity = velocity;
}

// =======================================================================
void Particle::SetGravityEnabled(bool val)
{
  m_GravityEnabled = val;
}

// =======================================================================
void Particle::AddVelocity(Vec3f velocity)
{
  m_Velocity += velocity;
}

// =======================================================================
Vec3f Particle::GetPosition() const
{
  return m_Position;
}

// =======================================================================
Vec3f Particle::GetVelocity() const
{
  return m_Velocity;
}

// =======================================================================
Vec3f Particle::GetAcceleration() const
{
  return m_Acceleration;
}

// =======================================================================
float Particle::GetMass() const
{
  return m_Mass;
}

// =======================================================================
float Particle::GetInverseMass() const
{
  return m_InverseMass;
}

// =======================================================================
bool Particle::IsGravityEnabled() const
{
  return m_GravityEnabled;
}

// =======================================================================
void Particle::SetRadius(float radius)
{
  m_Radius = radius;
}

// =======================================================================
float Particle::GetRadius() const
{
  return m_Radius;
}

// =======================================================================
void Particle::AddForce(Vec3f force)
{
  m_ForceAccumulator += force;
}

// =======================================================================
void Particle::Integrate(float dt)
{
  // position update
  m_Position += m_Velocity * dt;

  // acceleration update
  Vec3f resultAcceleration = m_Acceleration + m_ForceAccumulator * m_InverseMass;

  // velocity update
  m_Velocity += resultAcceleration * dt;
  m_Velocity *= powf(m_Damping, dt);

  m_ForceAccumulator.clear();
}

}  // namespace flux
