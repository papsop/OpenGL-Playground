#pragma once
#include <GLCore/Utils/Camera.h>

namespace GLCore {
class PerspectiveCamera : public I_Camera {
 public:
  PerspectiveCamera(glm::vec3 pos);
  ~PerspectiveCamera() = default;

  glm::vec2 ScreenToWorld(glm::vec2 pos) override;

 protected:
  void RecalculateProjectionMatrix() override;

  glm::mat4 m_viewMatrix;

  glm::vec3 m_cameraTarget;
  glm::vec3 m_cameraDirection;
  glm::vec3 m_cameraRight;
  glm::vec3 m_cameraUp;
};
}  // namespace GLCore
