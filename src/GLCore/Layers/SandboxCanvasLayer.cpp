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
  canvas_p0.y -= m_sandboxCanvas->GetHeight();

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

  // mouse wheel
  if (io.MouseWheel != 0.0f) {
    DISPATCH_EVENT(E_SandboxCanvasMouseEvent(E_SandboxCanvasMouseEvent::WheelUsed, io.MouseWheel, true));
  }
}

void SandboxCanvasLayer::OnImGuiUpdate(Timestep dt)
{
  ImGui::Begin(GetName());

  // Modify canvas size based on ImGui size
  int newWidth = static_cast<int>(ImGui::GetContentRegionAvail().x);
  int newHeight = static_cast<int>(ImGui::GetContentRegionAvail().y);

  if (newWidth != m_sandboxCanvas->GetWidth() || newHeight != m_sandboxCanvas->GetHeight()) {
    m_sandboxCanvas->ResizeCanvas(newWidth, newHeight);
  }

  // Scale everything according to canvas size
  void* texture = (void*)m_sandboxCanvas->GetTextureID();
  ImGui::ImageButton(texture, ImVec2(static_cast<float>(m_sandboxCanvas->GetWidth()), static_cast<float>(m_sandboxCanvas->GetHeight())), ImVec2(0, 1),
                     ImVec2(1, 0), 0);

  // ==================================
  // Debug yellow text of positions
  {
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
    canvas_p0.y -= m_sandboxCanvas->GetHeight();

    const ImVec2 mousePos = ImVec2(io.MousePos.x - canvas_p0.x, io.MousePos.y - canvas_p0.y);

    auto pos = ImGui::GetWindowPos();
    pos.x += 50.0f;
    pos.y += 50.0f;

    glm::vec2 screenPosition = {mousePos.x, mousePos.y};
    auto* camera = Application::Instance().GetMainCamera();
    glm::vec2 worldPosition = camera->ScreenToWorld(screenPosition);

    auto* drawList = ImGui::GetForegroundDrawList();
    char temp[255];
    sprintf_s(temp, "Screen: [%.2lf, %.2lf]\nWorld: [%.2lf, %.2lf]\nCanvas size [%.2lf, %.2lf]", screenPosition.x, screenPosition.y, worldPosition.x,
              worldPosition.y, camera->GetWidth(), camera->GetHeight());
    drawList->AddText(ImGui::GetFont(), ImGui::GetFontSize(), pos, ImColor(255, 255, 0, 255), temp, 0, 0.0f, 0);
  }

  if (ImGui::IsItemHovered()) {
    HandleCanvasMouseEvents();
  }

  ImGui::End();
}

}  // namespace GLCore
