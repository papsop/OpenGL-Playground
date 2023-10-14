#pragma once
#include <glm/glm.hpp>
#include <glm/vec2.hpp>

namespace GLCore {
class I_Camera {
 public:
  I_Camera() = default;
  virtual ~I_Camera() = default;

  virtual glm::vec2 ScreenToWorld(glm::vec2 pos) = 0;

  glm::mat4 GetProjection();
  glm::vec2 GetPosition();
  glm::vec2 GetSize();
  float GetZoom();

  void SetPosition(glm::vec3 pos);
  void SetZoom(float val);
  void SetCanvasSize(glm::vec2 size);
  void SetCameraMainSize(glm::vec2 size);

 protected:
  virtual void RecalculateProjectionMatrix() = 0;
  glm::mat4 m_projectionMatrix;
  glm::vec3 m_position;

  glm::vec2 m_canvasSize;          // size of ImGui canvas, used for aspect ratio calculation
  glm::vec2 m_cameraAspectedSize;  // this size is modified by aspect ratio and canvas size
  glm::vec2 m_cameraMainSize;      // this size will always be rendered

  float m_zoom;
};
}  // namespace GLCore
