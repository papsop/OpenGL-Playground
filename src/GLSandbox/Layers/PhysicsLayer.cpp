#include <GLSandbox/Layers/PhysicsLayer.h>
#include <GLCore/Core/Renderer.h>

namespace GLSandbox {

void PhysicsLayer::OnAttach()
{
  m_Particle.SetMass(1);
  m_Particle.SetDamping(0.95);
  m_Particle.SetAcceleration({0, -10.0f, 0});  // just g
}

void PhysicsLayer::OnUpdate(GLCore::Timestep dt)
{
  m_Particle.Integrate(dt);
  auto particlePos = m_Particle.GetPosition();
  GLCore::Renderer2D::Get()->DrawCircle({particlePos.x, particlePos.y}, 2.0f, {1.0f, 1.0f, 1.0f, 1.0f});
}

}  // namespace GLSandbox
