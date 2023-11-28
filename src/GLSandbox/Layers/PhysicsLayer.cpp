#include <GLSandbox/Layers/PhysicsLayer.h>

#include <GlCore/Utils/Log.h>
#include <GLCore/Core/Application.h>
#include <GLCore/Core/Renderer.h>

namespace GLSandbox
{

void PhysicsLayer::OnAttach()
{
  REGISTER_EVENT_CALLBACK(GLCore::E_SandboxCanvasMouseEvent, this, &PhysicsLayer::OnSandboxCanvasMouseEvent);

  m_World = std::make_unique<flux::World>();
  m_World->ConnectDebugger(&m_SandboxDebuggerAdapter);
  m_World->SetGravity({0.0f, -10.0f, 0.0f});

  m_ParticleWallA = m_World->CreateParticle();
  m_ParticleWallB = m_World->CreateParticle();
  m_ParticleWallC = m_World->CreateParticle();

  m_ParticleWallA->SetPosition({0.0f, -1004.0f, 0.0f});
  m_ParticleWallA->SetRadius(1000.0f);
  m_ParticleWallA->SetMass(0.0f);

  m_ParticleWallB->SetPosition({-1004.0f, 0.0f, 0.0f});
  m_ParticleWallB->SetRadius(1000.0f);
  m_ParticleWallB->SetMass(0.0f);

  m_ParticleWallC->SetPosition({1004.0f, 0.0f, 0.0f});
  m_ParticleWallC->SetRadius(1000.0f);
  m_ParticleWallC->SetMass(0.0f);

  // example ball
  auto* ball = m_World->CreateParticle();
  m_Balls.push_back(ball);

  ball->SetPosition({0.0f, 0.0f, 0.0f});
  ball->SetRadius(0.2f);
  ball->SetMass(10.0f);
  ball->SetGravityEnabled(true);
}

void PhysicsLayer::OnDetach()
{
  UNREGISTER_EVENT_CALLBACK(GLCore::E_SandboxCanvasMouseEvent, this);
  m_World->DisconnectDebugger();
}

void PhysicsLayer::OnUpdate(GLCore::Timestep dt)
{
  m_World->Step(dt);

  DebugDraw();
}

void PhysicsLayer::OnSandboxCanvasMouseEvent(const GLCore::E_SandboxCanvasMouseEvent& e)
{
  if (!m_enabled) return;
  glm::vec2 worldPos = GLCore::Application::Instance().GetMainCamera()->ScreenToWorld(e.Position);

  if (e.Type == GLCore::E_SandboxCanvasMouseEvent::LeftClickPressed)
  {
    auto* ball = m_World->CreateParticle();
    m_Balls.push_back(ball);

    ball->SetPosition({worldPos.x, worldPos.y, 0.0f});
    ball->SetRadius(0.2f);
    ball->SetMass(10.0f);
    ball->SetGravityEnabled(true);
  }
}

void PhysicsLayer::DebugDraw()
{
  m_World->DebugDraw();
}

}  // namespace GLSandbox
