#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Utils/OrtographicCamera.h>

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

  void OnSandboxCanvasResize(const SandboxCanvasEvent& event);
  void OnSandboxCanvasMouseEvent(const SandboxCanvasMouseEvent& event);

 private:
  OrthographicCamera* m_camera;
};
}  // namespace GLCore
