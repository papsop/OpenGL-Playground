#include <GLCore/Layers/CameraControlLayer.h>
#include <GLCore/Core/Application.h>

#include <imgui.h>

namespace GLCore {

void CameraControlLayer::OnAttach()
{
  m_camera = Application::Instance().GetMainCamera();

  REGISTER_EVENT_CALLBACK(E_SandboxCanvasEvent, this, &CameraControlLayer::OnSandboxCanvasResize);
  REGISTER_EVENT_CALLBACK(E_SandboxCanvasMouseEvent, this, &CameraControlLayer::OnSandboxCanvasMouseEvent);
}

void CameraControlLayer::OnDetach()
{
  UNREGISTER_EVENT_CALLBACK(E_SandboxCanvasEvent, this);
  UNREGISTER_EVENT_CALLBACK(E_SandboxCanvasMouseEvent, this);
}

void CameraControlLayer::OnSandboxCanvasResize(const E_SandboxCanvasEvent& event)
{
  if (event.Type == E_SandboxCanvasEvent::Resize) {
    m_camera->SetCanvasSize(event.Data.NewSize);
  }
}

void CameraControlLayer::OnSandboxCanvasMouseEvent(const E_SandboxCanvasMouseEvent& event)
{
  glm::vec2 mousePos = m_camera->ScreenToWorld(event.Position);

  if (event.Type == E_SandboxCanvasMouseEvent::RightClickPressed) {
    m_lastMousePos = mousePos;
  }

  if (event.Type == E_SandboxCanvasMouseEvent::RightClickDown) {
    glm::vec2 offset = mousePos - m_lastMousePos;
    offset.x *= -1.0f;
    m_camera->SetPosition(m_camera->GetPosition() + offset);

    m_lastMousePos = m_camera->ScreenToWorld(event.Position);  // recalculate, because Camera changed projection
  }
}

void CameraControlLayer::OnImGuiUpdate(Timestep dt)
{
  ImGui::Begin(GetName());

  {
    ImGui::Text("Zoom:");
    float val = m_camera->GetZoom();
    ImGui::SliderFloat("Zoom", &val, 0.0f, 10.0f);
    m_camera->SetZoom(val);
  }

  {
    ImGui::Text("Position:");
    ImGui::Text("[%.2lf, %.2lf]", m_camera->GetPosition().x, m_camera->GetPosition().y);
  }

  ImGui::End();
}
}  // namespace GLCore
