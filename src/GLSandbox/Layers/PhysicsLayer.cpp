#include <GLSandbox/Layers/PhysicsLayer.h>

#include <GlCore/Utils/Log.h>
#include <GLCore/Core/Application.h>
#include <GLCore/Core/Renderer.h>

#include <imgui.h>

namespace GLSandbox
{

void PhysicsLayer::OnAttach()
{
  REGISTER_EVENT_CALLBACK(GLCore::E_SandboxCanvasMouseEvent, this, &PhysicsLayer::OnSandboxCanvasMouseEvent);

  m_SandboxDebuggerAdapter.SetDrawBody(true);
  m_SandboxDebuggerAdapter.SetDrawDirection(false);

  m_World = std::make_unique<flux::World>();
  m_World->ConnectDebugger(&m_SandboxDebuggerAdapter);
  m_World->SetGravity({0.0f, -10.0f, 0.0f});

  m_ParticleWallA = m_World->CreateParticle();
  m_ParticleWallB = m_World->CreateParticle();
  m_ParticleWallC = m_World->CreateParticle();

  m_ParticleWallA->SetPosition({0.0f, -1004.0f, 0.0f});
  m_ParticleWallA->SetRadius(1000.0f);
  m_ParticleWallA->SetMass(0.0f);
  m_ParticleWallA->SetGravityEnabled(false);

  m_ParticleWallB->SetPosition({-1004.0f, 0.0f, 0.0f});
  m_ParticleWallB->SetRadius(1000.0f);
  m_ParticleWallB->SetMass(0.0f);
  m_ParticleWallB->SetGravityEnabled(false);

  m_ParticleWallC->SetPosition({1004.0f, 0.0f, 0.0f});
  m_ParticleWallC->SetRadius(1000.0f);
  m_ParticleWallC->SetMass(0.0f);
  m_ParticleWallC->SetGravityEnabled(false);

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
  // TODO: fixed update instead of updating every render frame
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

void PhysicsLayer::OnImGuiUpdate(GLCore::Timestep dt)
{
  if (!IsEnabled()) return;

  ImGui::Begin(GetName());

  ImGui::Text("Particle debug:");
  {
    bool valBody = m_SandboxDebuggerAdapter.ShouldDrawBody();
    ImGui::Checkbox("Body", &valBody);
    m_SandboxDebuggerAdapter.SetDrawBody(valBody);
  }
  {
    bool valDirection = m_SandboxDebuggerAdapter.ShouldDrawDirection();
    ImGui::Checkbox("Direction", &valDirection);
    m_SandboxDebuggerAdapter.SetDrawDirection(valDirection);
  }
  ImGui::Separator();
  ImGui::Text("Number of balls: %d", m_Balls.size());

  ImGui::End();
}

void PhysicsLayer::DebugDraw()
{
  m_World->DebugDraw();
}

}  // namespace GLSandbox
