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

  ImGui::End();
}
}  // namespace GLCore
