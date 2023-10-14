#pragma once
#include <GLCore/Utils/Camera.h>
#include <GLCore/Core/Events.h>

#include <glm/glm.hpp>

namespace GLCore {

class OrthographicCamera : public I_Camera {
 public:
  OrthographicCamera(glm::vec2 size, glm::vec3 position);
  ~OrthographicCamera() = default;

  virtual glm::vec2 ScreenToWorld(glm::vec2) override;

 private:
  glm::vec4 GetProjectionParams();
  virtual void RecalculateProjectionMatrix() override;

  glm::vec2 m_lastEventMousePosition;
};
}  // namespace GLCore
