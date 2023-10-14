#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Utils/Camera.h>

#include <GLCore/Core/Events.h>

namespace GLCore {
class CameraControlLayer : public I_Layer {
 public:
  CameraControlLayer() : I_Layer("Camera control")
  {
  }
  void OnImGuiUpdate(Timestep dt) override;

  void OnAttach() override;
  void OnDetach() override;

  void OnSandboxCanvasResize(const E_SandboxCanvasEvent& event);
  void OnSandboxCanvasMouseEvent(const E_SandboxCanvasMouseEvent& event);

 private:
  I_Camera* m_camera;

  glm::vec2 m_lastMousePos;
  float m_mouseWheelSensitivity = 0.3f;
};
}  // namespace GLCore
