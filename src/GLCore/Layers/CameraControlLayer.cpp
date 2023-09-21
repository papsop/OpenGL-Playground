#include <GLCore/Layers/CameraControlLayer.h>
#include <GLCore/Core/Application.h>

#include <imgui.h>

namespace GLCore {

void CameraControlLayer::OnAttach()
{
  m_camera = Application::Instance().GetMainCamera();

  REGISTER_EVENT_CALLBACK(SandboxCanvasEvent, this, &CameraControlLayer::OnSandboxCanvasResize);
  REGISTER_EVENT_CALLBACK(SandboxCanvasMouseEvent, this, &CameraControlLayer::OnSandboxCanvasMouseEvent);
}

void CameraControlLayer::OnDetach()
{
  UNREGISTER_EVENT_CALLBACK(SandboxCanvasEvent, this);
  UNREGISTER_EVENT_CALLBACK(SandboxCanvasMouseEvent, this);
}

void CameraControlLayer::OnSandboxCanvasResize(const SandboxCanvasEvent& event)
{
}

void CameraControlLayer::OnSandboxCanvasMouseEvent(const SandboxCanvasMouseEvent& event)
{
}

void CameraControlLayer::OnImGuiUpdate(Timestep dt)
{
  ImGui::Begin(GetName());

  ImGui::End();
}
}  // namespace GLCore
