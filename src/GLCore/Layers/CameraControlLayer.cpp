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
    LOG_INFO("Updating to [{0}, {1}]", event.Width, event.Height);
    m_camera->SetCanvasSize({event.Width, event.Height});
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

    glm::vec3 newPos = glm::vec3(m_camera->GetPosition() - offset, -3);
    m_camera->SetPosition(newPos);  // subtract, so the position follows mouse instead of reverse

    m_lastMousePos = m_camera->ScreenToWorld(event.Position);  // previous lastMousePos is invalid because of setting a new position
  }

  if (event.Type == E_SandboxCanvasMouseEvent::WheelUsed) {
    m_camera->SetZoom(m_camera->GetZoom() + (event.Wheel * m_mouseWheelSensitivity));
  }
}

void CameraControlLayer::OnImGuiUpdate(Timestep dt)
{
  ImGui::Begin(GetName());

  ImGui::Text("Camera type:");
  int selectedCamera = Application::Instance().GetActiveCameraIndex();
  ImGui::RadioButton("Orthographic", &selectedCamera, 0);
  ImGui::RadioButton("Perspective", &selectedCamera, 1);
  Application::Instance().SetActiveCameraIndex(selectedCamera);

  ImGui::Separator();
  ImGui::Text("Settings:");

  ImGui::Separator();
  ImGui::Text("Zoom:");
  float zoom = m_camera->GetZoom();
  ImGui::SliderFloat("Zoom", &zoom, 0.0f, 10.0f);
  m_camera->SetZoom(zoom);

  ImGui::Separator();
  ImGui::Text("Debug info: ");
  ImGui::Text("Position (world): [%.2lf, %.2lf]", m_camera->GetPosition().x, m_camera->GetPosition().y);
  ImGui::Text("Zoom: %.2lf", m_camera->GetZoom());

  ImGui::End();
}
}  // namespace GLCore
