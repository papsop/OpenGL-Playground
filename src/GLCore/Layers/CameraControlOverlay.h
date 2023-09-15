#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Utils/OrtographicCamera.h>

namespace GLCore {
class CameraControlOverlay : public I_Layer {
 public:
  CameraControlOverlay() : I_Layer("Camera control")
  {
  }
  void OnImGuiUpdate(Timestep dt) override;

  void OnAttach() override;

 private:
  OrthographicCamera* m_camera;
};
}  // namespace GLCore
