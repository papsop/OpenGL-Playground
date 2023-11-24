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
  void AddVelocity(Vec3f velocity);

  Vec3f GetPosition() const;
  Vec3f GetVelocity() const;
  Vec3f GetAcceleration() const;
  float GetMass() const;
  float GetInverseMass() const;

  // PLACEHOLDER CIRCLE COLLISION DETECTION
  void SetRadius(float radius);
  float GetRadius() const;

  void AddForce(Vec3f force);

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

  float m_Damping;  // damps velocity every update, fixes floating point inaccuracies
  float m_Mass;
  float m_InverseMass;  // pre-calculated for equations

  // PLACEHOLDER CIRCLE COLLISION DETECTION
  float m_Radius;
};
}  // namespace flux
