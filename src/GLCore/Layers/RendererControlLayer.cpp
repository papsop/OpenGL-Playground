#include <GLCore/Layers/RendererControlLayer.h>
#include <GLCore/Core/Application.h>
#include <imgui.h>

namespace GLCore {

void RendererControlLayer::OnImGuiUpdate(Timestep dt)
{
  ImGui::Begin(GetName());

  ImGui::End();
}

void RendererControlLayer::OnAttach()
{
  m_renderer = Application::Instance().GetRenderer();
}

}  // namespace GLCore
