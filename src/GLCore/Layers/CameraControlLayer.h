#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Utils/OrtographicCamera.h>

namespace GLCore {
class CameraControlLayer : public I_Layer {
 public:
  CameraControlLayer() : I_Layer("Camera control")
  {
  }
  void OnImGuiUpdate(Timestep dt) override;

  void OnAttach() override;

 private:
  OrthographicCamera* m_camera;
};
}  // namespace GLCore
