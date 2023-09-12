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
  // ================================================
  ImGuiWindowFlags windowFlags = ImGuiWindowFlags_AlwaysAutoResize;
  ImGui::Begin("Application control", NULL, windowFlags);
  ImGui::Separator();
  ImGui::Text("FPS:");
  ImGui::BulletText("FPS: %.1lf", 1000.0f / dt.GetMilliseconds());
  ImGui::BulletText("Frame time (ms): %.3f", dt.GetMilliseconds());

  m_fpsValues[m_fpsValueOffset] = dt.GetMilliseconds();
  m_fpsValueOffset = (m_fpsValueOffset + 1) % IM_ARRAYSIZE(m_fpsValues);
  {
    float average = 0.0f;
    for (int n = 0; n < IM_ARRAYSIZE(m_fpsValues); n++) {
      average += m_fpsValues[n];
    }
    average /= (float)IM_ARRAYSIZE(m_fpsValues);
    char overlay[32];
    sprintf(overlay, "avg %.3fms", average);

    ImGui::PlotLines("Frame times", m_fpsValues, IM_ARRAYSIZE(m_fpsValues), m_fpsValueOffset, overlay, 0.0f, 1.0f, ImVec2(0, 80.0f));
  }
  // ================================================
  ImGui::Separator();
  ImGui::Text("LAYERS:");
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
