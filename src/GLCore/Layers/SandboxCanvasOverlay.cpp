#include <GLCore/Layers/SandboxCanvasOverlay.h>
#include <GLCore/Utils/Log.h>
#include <GLCore/Core/Application.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>

namespace GLCore {

void SandboxCanvasOverlay::OnAttach()
{
  m_sandboxCanvas = Application::Instance().GetSandboxCanvas();
}

void SandboxCanvasOverlay::OnDetach()
{
  m_sandboxCanvas = nullptr;
}

void SandboxCanvasOverlay::OnImGuiUpdate(Timestep dt)
{
  ImGui::Begin(GetName());

  float width = ImGui::GetContentRegionAvail().x;
  float height = ImGui::GetContentRegionAvail().y;

  m_sandboxCanvas->ResizeCanvas({width, height});
  void* texture = (void*)m_sandboxCanvas->GetTextureID();

  ImGui::Image(texture, ImVec2(width, height), ImVec2(0, 1), ImVec2(1, 0));

  ImGui::End();
}

}  // namespace GLCore
