#include <GLSandbox/Layers/DrawingLayer.h>
#include <GLCore/Core/Application.h>

namespace GLSandbox {
void GLSandbox::DrawingLayer::OnUpdate(GLCore::Timestep dt)
{
  GLCore::Renderer2D::Get()->DrawLine({0.0, 0.0f}, {5.0f, 5.0f}, {1.0f, 0.0f, 0.0f, 1.0f});
  GLCore::Renderer2D::Get()->DrawLine({0.0, 0.0f}, {5.0f, -5.0f}, {0.0f, 1.0f, 0.0f, 1.0f});
  GLCore::Renderer2D::Get()->DrawLine({0.0, 0.0f}, {-5.0f, -5.0f}, {0.0f, 0.0f, 1.0f, 1.0f});
  GLCore::Renderer2D::Get()->DrawLine({0.0, 0.0f}, {-5.0f, 5.0f}, {1.0f, 0.0f, 1.0f, 1.0f});

  GLCore::Renderer2D::Get()->DrawCircle({0.0, 0.0f}, 2.0f, {1.0f, 1.0f, 1.0f, 1.0f});

  for (auto& line : m_lines) {
    GLCore::Renderer2D::Get()->DrawLine(line.first, line.second, {1.0f, 0.0f, 0.0f, 1.0f});
  }

  if (m_drawing) {
    GLCore::Renderer2D::Get()->DrawLine(m_linePreview.first, m_linePreview.second, {1.0f, 1.0f, 0.0f, .5f});
  }
}
void DrawingLayer::OnSandboxCanvasMouseEvent(const GLCore::E_SandboxCanvasMouseEvent& e)
{
  // LOG_INFO("received leftclick p mouse event");

  glm::vec2 worldPos = GLCore::Application::Instance().GetMainCamera()->ScreenToWorld(e.Position);

  // Drawing
  if (e.Type == GLCore::E_SandboxCanvasMouseEvent::LeftClickPressed) {
    m_lastPoint = worldPos;
    m_linePreview = std::make_pair(m_lastPoint, m_lastPoint);
    m_drawing = true;
  }
  else if (e.Type == GLCore::E_SandboxCanvasMouseEvent::LeftClickReleased && m_drawing) {
    m_lines.push_back(std::make_pair(m_lastPoint, worldPos));
    m_drawing = false;
  }

  // Cancel drawing
  if (e.Type == GLCore::E_SandboxCanvasMouseEvent::RightClickReleased) {
    m_drawing = false;
  }

  // Preview
  if (e.Type == GLCore::E_SandboxCanvasMouseEvent::LeftClickDown) {
    m_linePreview = std::make_pair(m_lastPoint, worldPos);
  }
}
void DrawingLayer::OnAttach()
{
  REGISTER_EVENT_CALLBACK(GLCore::E_SandboxCanvasMouseEvent, this, &DrawingLayer::OnSandboxCanvasMouseEvent);
}

void DrawingLayer::OnDetach()
{
  UNREGISTER_EVENT_CALLBACK(GLCore::E_SandboxCanvasMouseEvent, this);
}

}  // namespace GLSandbox
