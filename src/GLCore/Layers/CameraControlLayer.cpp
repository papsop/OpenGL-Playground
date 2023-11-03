#include <GLCore/Layers/CameraControlLayer.h>
#include <GLCore/Core/Application.h>

#include <imgui.h>

namespace GLCore {

void CameraControlLayer::OnAttach()
{
  REGISTER_EVENT_CALLBACK(E_SandboxCanvasEvent, this, &CameraControlLayer::OnSandboxCanvasResize);
  REGISTER_EVENT_CALLBACK(E_SandboxCanvasMouseEvent, this, &CameraControlLayer::OnSandboxCanvasMouseEvent);
  REGISTER_EVENT_CALLBACK(E_KeyInputEvent, this, &CameraControlLayer::OnKeyInputEvent);
}

void CameraControlLayer::OnDetach()
{
  UNREGISTER_EVENT_CALLBACK(E_SandboxCanvasEvent, this);
  UNREGISTER_EVENT_CALLBACK(E_SandboxCanvasMouseEvent, this);
  UNREGISTER_EVENT_CALLBACK(E_KeyInputEvent, this);
}

void CameraControlLayer::OnSandboxCanvasResize(const E_SandboxCanvasEvent& event)
{
  if (event.Type == E_SandboxCanvasEvent::Resize) {
    Application::Instance().GetMainCamera()->SetCanvasSize({event.Width, event.Height});
  }
}

void CameraControlLayer::OnSandboxCanvasMouseEvent(const E_SandboxCanvasMouseEvent& event)
{
  auto camera = Application::Instance().GetMainCamera();

  if (camera->GetCameraType() == E_CameraType::ORTHOGRAPHIC) {
    glm::vec2 mousePos = camera->ScreenToWorld(event.Position);
    if (event.Type == E_SandboxCanvasMouseEvent::RightClickPressed) {
      m_lastMousePos = mousePos;
    }

    if (event.Type == E_SandboxCanvasMouseEvent::RightClickDown) {
      glm::vec3 offset = glm::vec3(mousePos - m_lastMousePos, 0);
      glm::vec3 newPos = camera->GetPosition() - offset;
      newPos.z = camera->GetPosition().z;
      camera->SetPosition(newPos);  // subtract, so the position follows mouse instead of reverse

      m_lastMousePos = camera->ScreenToWorld(event.Position);  // previous lastMousePos is invalid because of setting a new position
    }

    if (event.Type == E_SandboxCanvasMouseEvent::WheelUsed) {
      camera->SetZoom(camera->GetZoom() + (event.Wheel * m_mouseWheelSensitivity));
    }
  }
  else if (camera->GetCameraType() == E_CameraType::PERSPECTIVE) {
    if (event.Type == E_SandboxCanvasMouseEvent::LeftClickDown) {
    }

    if (event.Type == E_SandboxCanvasMouseEvent::WheelUsed) {
      camera->SetZoom(camera->GetZoom() + (event.Wheel * m_mouseWheelSensitivity));
    }
  }
}

void CameraControlLayer::OnKeyInputEvent(const E_KeyInputEvent& event)
{
}

void CameraControlLayer::OnImGuiUpdate(Timestep dt)
{
  auto camera = Application::Instance().GetMainCamera();
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
  float zoom = camera->GetZoom();
  ImGui::SliderFloat("Zoom", &zoom, 0.1f, 10.0f);
  camera->SetZoom(zoom);

  ImGui::Separator();
  ImGui::Text("Debug info: ");
  auto pos = camera->GetPosition();
  ImGui::Text("Position (world): [%.2lf, %.2lf, %.2lf]", pos.x, pos.y, pos.z);
  auto target = camera->GetTarget();
  ImGui::Text("Target: [%.2lf, %.2lf, %.2lf]", target.x, target.y, target.z);
  ImGui::Text("Zoom: %.2lf", camera->GetZoom());

  ImGui::End();
}
}  // namespace GLCore
