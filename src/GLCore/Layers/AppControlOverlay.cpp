#include <GLCore/Layers/AppControlOverlay.h>
#include <GLCore/Core/Application.h>
#include <GLCore/Utils/Log.h>

#include <imgui.h>

namespace GLCore {

void AppControlOverlay::OnAttach()
{
  m_layerStack = Application::Instance().GetLayerStack();
}

void AppControlOverlay::OnDetach()
{
}

void AppControlOverlay::OnFrameBegin()
{
}

void AppControlOverlay::OnUpdate(Timestep dt)
{
}

void AppControlOverlay::OnImGuiUpdate(Timestep dt)
{
  ImGuiWindowFlags windowFlags = ImGuiWindowFlags_AlwaysAutoResize;
  ImGui::Begin("Application control", NULL, windowFlags);
  ImGui::Text("FPS: %.1lf", 1000.0f / dt.GetMilliseconds());
  ImGui::Text("Frame time (ms): %.5lf", dt.GetMilliseconds());
  ImGui::Separator();
  ImGui::Text("Layers");
  for (auto& layer : *m_layerStack) {
    ImGui::BeginDisabled(layer->IsLocked());

    bool temp = layer->IsEnabled();
    ImGui::Checkbox(layer->GetName(), &temp);
    layer->SetEnabled(temp);

    ImGui::EndDisabled();

    if (layer->IsLocked()) {
      ImGui::SameLine();
      ImGui::TextDisabled("(?)");
      if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted("This layer is locked and therefore cannot be disabled");
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
      }
    }
  }

  ImGui::End();
}

void AppControlOverlay::OnFrameEnd()
{
}

}  // namespace GLCore
