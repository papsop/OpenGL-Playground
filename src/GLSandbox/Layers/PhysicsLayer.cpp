#include <GLSandbox/Layers/PhysicsLayer.h>

#include <GlCore/Utils/Log.h>
#include <GLCore/Core/Renderer.h>

namespace GLSandbox {

void PhysicsLayer::OnAttach()
{
  m_World = std::make_unique<flux::World>();

  m_Particle = m_World->CreateParticle();

  m_World->RegisterForceGenerator(&m_GravityForceGenerator, m_Particle);

  m_Particle->SetMass(10.0f);
  m_Particle->SetDamping(0.95f);
  // m_Particle->SetVelocity({10.0f, 0, 0});
}

void PhysicsLayer::OnUpdate(GLCore::Timestep dt)
{
  m_World->Step(dt);

  // debug draw
  auto particlePos = m_Particle->GetPosition();
  GLCore::Renderer2D::Get()->DrawCircle({particlePos.x, particlePos.y}, .5f, {1.0f, 1.0f, 1.0f, 1.0f});

  // auto v = m_Particle->GetVelocity();
  // LOG_INFO("velocity: {0}, {1}, {2}", v.x, v.y, v.z);
}

}  // namespace GLSandbox
