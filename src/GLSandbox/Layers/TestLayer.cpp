#include <GLSandbox/Layers/TestLayer.h>
#include <GLCore/Core/Application.h>

namespace GLSandbox {
void GLSandbox::TestLayer::OnUpdate(GLCore::Timestep dt)
{
  GLCore::Renderer2D::Get()->DrawLine({0.0, 0.0f}, {5.0f, 5.0f}, {1.0f, 0.0f, 0.0f, 1.0f});
  GLCore::Renderer2D::Get()->DrawLine({0.0, 0.0f}, {5.0f, -5.0f}, {0.0f, 1.0f, 0.0f, 1.0f});

  for (auto& line : m_lines) {
    GLCore::Renderer2D::Get()->DrawLine(line.first, line.second, {1.0f, 0.0f, 0.0f, 1.0f});
  }
}

void TestLayer::OnSandboxCanvasMouseEvent(const GLCore::SandboxCanvasMouseEvent& e)
{
  if (e.Type != GLCore::SandboxCanvasMouseEvent::LeftClickPressed && e.Type != GLCore::SandboxCanvasMouseEvent::LeftClickReleased) return;
  // LOG_INFO("received leftclick p mouse event");

  glm::vec2 worldPos = GLCore::Application::Instance().GetMainCamera()->ScreenToWorld(e.Position);

  if (e.Type == GLCore::SandboxCanvasMouseEvent::LeftClickPressed) {
    m_lastPoint = worldPos;
  }
  else if (e.Type == GLCore::SandboxCanvasMouseEvent::LeftClickReleased) {
    m_lines.push_back(std::make_pair(m_lastPoint, worldPos));
    LOG_INFO("Adding line between [{0}, {1}] and [{2}, {3}]", m_lastPoint.x, m_lastPoint.y, worldPos.x, worldPos.y);
  }
}
void TestLayer::OnAttach()
{
  REGISTER_EVENT_CALLBACK(GLCore::SandboxCanvasMouseEvent, this, &TestLayer::OnSandboxCanvasMouseEvent);
}

void TestLayer::OnDetach()
{
  // todo add unregister callback
}

}  // namespace GLSandbox
