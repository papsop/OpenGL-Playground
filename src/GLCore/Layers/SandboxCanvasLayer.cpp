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
  // ============================================
  // Canvas

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

  if (ImGui::IsItemHovered()) {
    HandleCanvasMouseEvents();
  }

  // Needs to be within the canvas scope
  ImGuiIO& io = ImGui::GetIO();
  ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
  // GetCursorScreenPos points at the end of last element, so delete canvas' height to get to the top
  canvas_p0.y -= m_sandboxCanvas->GetHeight();
  const ImVec2 mousePos = ImVec2(io.MousePos.x - canvas_p0.x, io.MousePos.y - canvas_p0.y);
  auto canvasViewport = ImGui::GetWindowViewport();
  ImGui::End();

  // ============================================
  // Overlay
  GL_TODO("Overlay should follow canvas even when it's undocked and in its own viewport");

  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize |
                                  ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

  auto overlayPos = canvas_p0;
  overlayPos.x += 15.0f;
  overlayPos.y += 15.0f;
  ImGui::SetNextWindowPos(overlayPos, ImGuiCond_Always, {0, 0});
  ImGui::SetNextWindowBgAlpha(0.7f);                 // Transparent background
  ImGui::SetNextWindowViewport(canvasViewport->ID);  // always use the same viewport as canvas, doesn't work I guess

  if (ImGui::Begin("SandboxCanvasInfo", NULL, window_flags)) {
    auto* camera = Application::Instance().GetMainCamera();
    glm::vec2 screenPosition = {mousePos.x, mousePos.y};
    glm::vec2 worldPosition = camera->ScreenToWorld(screenPosition);
    ImGui::Text("Sandbox canvas info:");
    ImGui::Text("Camera index %d", Application::Instance().GetActiveCameraIndex());
    ImGui::Text("Screen cursor: [%.2lf, %.2lf]", screenPosition.x, screenPosition.y);
    ImGui::Text("World cursor: [%.2lf, %.2lf]", worldPosition.x, worldPosition.y);
  }

  ImGui::End();
}

}  // namespace GLCore
