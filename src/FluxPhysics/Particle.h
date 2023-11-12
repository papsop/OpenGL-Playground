#pragma once
#include <FluxPhysics/Utils/Vec.h>

namespace flux {
class Particle {
 public:
  void SetMass(float mass);
  void SetDamping(float damp);
  void SetAcceleration(Vec3f acceleration);
  void SetVelocity(Vec3f velocity);

  Vec3f GetPosition() const;
  Vec3f GetVelocity() const;
  Vec3f GetAcceleration() const;

  void Integrate(float dt);

 private:
  Vec3f m_Position;
  Vec3f m_Velocity;
  Vec3f m_Acceleration;

  Vec3f m_ForceAccumulator;

  float m_Damping;  // damps velocity every update, fixes floating point inaccuracies
  float m_Mass;
  float m_InverseMass;  // pre-calculated for equations
};
}  // namespace flux
