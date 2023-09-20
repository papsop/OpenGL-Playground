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

void SandboxCanvasOverlay::HandleCanvasMouseEvents()
{
  ImGuiIO& io = ImGui::GetIO();
  const ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
  const ImVec2 mousePos = ImVec2(io.MousePos.x - canvas_p0.x, io.MousePos.y - canvas_p0.y);
  // LEFT
  if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
    DISPATCH_EVENT(MouseInputEvent(MouseInputEvent::LeftClickPressed, {mousePos.x, mousePos.y}, true));
  }

  if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
    DISPATCH_EVENT(MouseInputEvent(MouseInputEvent::LeftClickReleased, {mousePos.x, mousePos.y}, true));
  }

  // RIGHT
  if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
    DISPATCH_EVENT(MouseInputEvent(MouseInputEvent::RightClickPressed, {mousePos.x, mousePos.y}, true));
  }

  if (ImGui::IsMouseReleased(ImGuiMouseButton_Right)) {
    DISPATCH_EVENT(MouseInputEvent(MouseInputEvent::RightClickReleased, {mousePos.x, mousePos.y}, true));
  }
}

void SandboxCanvasOverlay::OnImGuiUpdate(Timestep dt)
{
  ImGui::Begin(GetName());

  float width = ImGui::GetContentRegionAvail().x;
  float height = ImGui::GetContentRegionAvail().y;

  m_sandboxCanvas->ResizeCanvas({width, height});
  void* texture = (void*)m_sandboxCanvas->GetTextureID();

  ImGui::ImageButton(texture, ImVec2(width, height), ImVec2(0, 1), ImVec2(1, 0), 0);

  if (ImGui::IsItemHovered()) {
    HandleCanvasMouseEvents();
  }

  ImGui::End();
}

}  // namespace GLCore
