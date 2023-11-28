#pragma once
#include <FluxPhysics/Utils/Vec.h>

namespace flux
{
class World;

// TODO: add particle ID?
class Particle
{
 public:
  void Destroy();

  void SetPosition(Vec3f position);
  void SetMass(float mass);
  void SetDamping(float damp);
  void SetAcceleration(Vec3f acceleration);
  void SetVelocity(Vec3f velocity);
  void SetGravityEnabled(bool val);

  Vec3f GetPosition() const;
  Vec3f GetVelocity() const;
  Vec3f GetAcceleration() const;
  float GetMass() const;
  float GetInverseMass() const;
  bool IsGravityEnabled() const;

  void AddForce(Vec3f force);
  void AddVelocity(Vec3f velocity);

  // PLACEHOLDER CIRCLE COLLISION DETECTION
  void SetRadius(float radius);
  float GetRadius() const;
  // ==========================================

 protected:
  Particle(World* world);
  void Integrate(float dt);
  friend class World;  // only world can create new particles

 private:
  World* m_World;

  Vec3f m_Position;
  Vec3f m_Velocity;
  Vec3f m_Acceleration;

  Vec3f m_ForceAccumulator;

  float m_Damping = 0.95f;  // damps velocity every update, fixes floating point inaccuracies
  float m_Mass;
  float m_InverseMass;  // pre-calculated for equations
  bool m_GravityEnabled;

  // PLACEHOLDER CIRCLE COLLISION DETECTION
  float m_Radius;
};
}  // namespace flux
