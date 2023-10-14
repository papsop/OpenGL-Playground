#pragma once
#include <GLCore/Utils/Camera.h>

namespace GLCore {
class PerspectiveCamera : public I_Camera {
 public:
  glm::vec2 ScreenToWorld(glm::vec2 pos) override;

 protected:
  void RecalculateProjectionMatrix() override;
};
}  // namespace GLCore
