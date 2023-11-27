#include <GLSandbox/Layers/PhysicsLayer.h>

#include <GlCore/Utils/Log.h>
#include <GLCore/Core/Renderer.h>

namespace GLSandbox
{

void PhysicsLayer::OnAttach()
{
  m_World = std::make_unique<flux::World>();
  m_World->ConnectDebugger(&m_SandboxDebuggerAdapter);

  m_ParticleA = m_World->CreateParticle();
  m_ParticleB = m_World->CreateParticle();

  m_ParticleA->SetPosition({0.0f, 0.0f, 0.0f});
  m_ParticleA->SetMass(10.0f);
  m_ParticleA->SetDamping(0.95f);
  m_ParticleA->SetRadius(0.2f);

  m_ParticleB->SetPosition({0.0f, 1.0f, 0.0f});
  m_ParticleB->SetMass(10.0f);
  m_ParticleB->SetDamping(0.95f);
  m_ParticleB->SetRadius(0.2f);

  m_ParticleB->SetVelocity({0.0f, -2.0f, 0.0f});

  // m_Particle->Destroy();
}

void PhysicsLayer::OnDetach()
{
  m_World->DisconnectDebugger();
}

void PhysicsLayer::OnUpdate(GLCore::Timestep dt)
{
  m_World->Step(dt);

  DebugDraw();
}

void PhysicsLayer::DebugDraw()
{
  m_World->DebugDraw();
  // GLCore::Renderer2D::Get()->DrawCircle({m_ParticleA->GetPosition().x, m_ParticleA->GetPosition().y}, m_ParticleA->GetRadius(), {1.0f, 1.0f, 1.0f, 1.0f});
  // GLCore::Renderer2D::Get()->DrawCircle({m_ParticleB->GetPosition().x, m_ParticleB->GetPosition().y}, m_ParticleB->GetRadius(), {1.0f, 0.0f, 1.0f, 1.0f});
}

}  // namespace GLSandbox
