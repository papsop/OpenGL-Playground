#pragma once
#include <glm/glm.hpp>

namespace GLCore {
class I_Camera {
 public:
  I_Camera() = default;
  virtual ~I_Camera() = default;

  virtual glm::vec2 ScreenToWorld() = 0;

  glm::mat4 GetProjection();
  glm::vec2 GetPosition();
  float GetZoom();

  void SetPosition(glm::vec3 pos);
  void SetZoom(float val);

 protected:
  virtual void RecalculateProjectionMatrix() = 0;
  glm::mat4 m_projectionMatrix;
  glm::vec3 m_position;
  float m_zoom;
};
}  // namespace GLCore
