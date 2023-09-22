#include <GLCore/Layers/SandboxCanvasLayer.h>
#include <GLCore/Utils/Log.h>
#include <GLCore/Core/Application.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>

namespace GLCore {

void SandboxCanvasLayer::OnAttach()
{
  m_sandboxCanvas = Application::Instance().GetSandboxCanvas();
}

void SandboxCanvasLayer::OnDetach()
{
  m_sandboxCanvas = nullptr;
}

void SandboxCanvasLayer::HandleCanvasMouseEvents()
{
  ImGuiIO& io = ImGui::GetIO();
  ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
  // GetCursorScreenPos points at the end of last element, so delete canvas' height to get to the top
  canvas_p0.y -= m_sandboxCanvas->GetSize().y;

  const ImVec2 mousePos = ImVec2(io.MousePos.x - canvas_p0.x, io.MousePos.y - canvas_p0.y);
  // LEFT
  if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
    DISPATCH_EVENT(E_SandboxCanvasMouseEvent(E_SandboxCanvasMouseEvent::LeftClickPressed, {mousePos.x, mousePos.y}, true));
  }

  if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
    DISPATCH_EVENT(E_SandboxCanvasMouseEvent(E_SandboxCanvasMouseEvent::LeftClickReleased, {mousePos.x, mousePos.y}, true));
  }

  if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
    DISPATCH_EVENT(E_SandboxCanvasMouseEvent(E_SandboxCanvasMouseEvent::LeftClickDown, {mousePos.x, mousePos.y}, true));
  }

  // RIGHT
  if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
    DISPATCH_EVENT(E_SandboxCanvasMouseEvent(E_SandboxCanvasMouseEvent::RightClickPressed, {mousePos.x, mousePos.y}, true));
  }

  if (ImGui::IsMouseReleased(ImGuiMouseButton_Right)) {
    DISPATCH_EVENT(E_SandboxCanvasMouseEvent(E_SandboxCanvasMouseEvent::RightClickReleased, {mousePos.x, mousePos.y}, true));
  }

  if (ImGui::IsMouseDown(ImGuiMouseButton_Right)) {
    DISPATCH_EVENT(E_SandboxCanvasMouseEvent(E_SandboxCanvasMouseEvent::RightClickDown, {mousePos.x, mousePos.y}, true));
  }
}

void SandboxCanvasLayer::OnImGuiUpdate(Timestep dt)
{
  ImGui::Begin(GetName());

  glm::vec2 canvasPanelSize = {ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y};

  if (canvasPanelSize != m_sandboxCanvas->GetSize()) {
    m_sandboxCanvas->ResizeCanvas(canvasPanelSize);
  }
  void* texture = (void*)m_sandboxCanvas->GetTextureID();

  ImGui::ImageButton(texture, ImVec2(canvasPanelSize.x, canvasPanelSize.y), ImVec2(0, 1), ImVec2(1, 0), 0);

  // ==================================
  // Debug yellow text of positions
  {
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
    canvas_p0.y -= canvasPanelSize.y;

    const ImVec2 mousePos = ImVec2(io.MousePos.x - canvas_p0.x, io.MousePos.y - canvas_p0.y);

    auto pos = ImGui::GetWindowPos();
    pos.x += 100.0f;
    pos.y += 100.0f;

    glm::vec2 screenPosition = {mousePos.x, mousePos.y};
    glm::vec2 worldPosition = Application::Instance().GetMainCamera()->ScreenToWorld(screenPosition);

    auto* drawList = ImGui::GetForegroundDrawList();
    char temp[255];
    sprintf(temp, "Screen: [%.2lf, %.2lf]\nWorld: [%.2lf, %.2lf]", screenPosition.x, screenPosition.y, worldPosition.x, worldPosition.y);
    drawList->AddText(ImGui::GetFont(), ImGui::GetFontSize(), pos, ImColor(255, 255, 0, 255), temp, 0, 0.0f, 0);
  }

  if (ImGui::IsItemHovered()) {
    HandleCanvasMouseEvents();
  }

  ImGui::End();
}

}  // namespace GLCore
