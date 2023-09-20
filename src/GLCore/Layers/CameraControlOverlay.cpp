#include <GLCore/Layers/CameraControlOverlay.h>
#include <GLCore/Core/Application.h>

#include <imgui.h>

namespace GLCore {

void CameraControlOverlay::OnAttach()
{
  m_camera = Application::Instance().GetMainCamera();
}

void CameraControlOverlay::OnImGuiUpdate(Timestep dt)
{
  ImGui::Begin(GetName());
  OrthographicCameraData cameraData = m_camera->GetCameraData();
  if (ImGui::Button("Reset to default")) {
    m_camera->ResetToDefaultData();
  }
  else {
    ImGui::Text("Camera settings:");
    ImGui::SliderFloat("Left", &cameraData.Borders[0], -10.0f, 10.0f);
    ImGui::SliderFloat("Right", &cameraData.Borders[1], -10.0f, 10.0f);
    ImGui::SliderFloat("Bottom", &cameraData.Borders[2], -10.0f, 10.0f);
    ImGui::SliderFloat("Top", &cameraData.Borders[3], -10.0f, 10.0f);

    ImGui::Text("Position");
    ImGui::SliderFloat("x", &cameraData.Position[0], -10.0f, 10.0f);
    ImGui::SliderFloat("y", &cameraData.Position[1], -10.0f, 10.0f);
    m_camera->SetCameraData(cameraData);
  }

  ImGui::End();
}
}  // namespace GLCore
