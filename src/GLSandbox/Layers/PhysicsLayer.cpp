#include <GLSandbox/Layers/PhysicsLayer.h>

#include <GlCore/Utils/Log.h>
#include <GLCore/Core/Renderer.h>

namespace GLSandbox
{

void PhysicsLayer::OnAttach()
{
  m_World = std::make_unique<flux::World>();
  m_World->ConnectDebugger(&m_SandboxDebuggerAdapter);
  m_World->SetGravity({0.0f, -10.0f, 0.0f});

  m_ParticleA = m_World->CreateParticle();
  m_ParticleB = m_World->CreateParticle();
  m_ParticleC = m_World->CreateParticle();

  m_ParticleA->SetPosition({0.0f, 0.0f, 0.0f});
  m_ParticleA->SetMass(0.0f);  // immovable
  m_ParticleA->SetDamping(0.95f);
  m_ParticleA->SetRadius(0.3f);
  m_ParticleA->SetGravityEnabled(false);

  m_ParticleB->SetPosition({0.0f, 5.0f, 0.0f});
  m_ParticleB->SetMass(5.0f);
  m_ParticleB->SetDamping(0.95f);
  m_ParticleB->SetRadius(0.2f);
  m_ParticleB->SetGravityEnabled(true);

  m_ParticleC->SetPosition({0.1f, 7.0f, 0.0f});
  m_ParticleC->SetMass(5.0f);
  m_ParticleC->SetDamping(0.95f);
  m_ParticleC->SetRadius(0.2f);
  m_ParticleC->SetGravityEnabled(true);
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
}

}  // namespace GLSandbox
