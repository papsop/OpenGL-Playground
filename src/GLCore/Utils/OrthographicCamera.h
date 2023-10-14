#pragma once
#include <GLCore/Core/Events.h>

#include <glm/glm.hpp>

namespace GLCore {

class OrthographicCamera {
 public:
  OrthographicCamera() = default;
  ~OrthographicCamera() = default;

  void Create(glm::vec2 size, glm::vec2 position);

  void SetPosition(glm::vec2 position);
  void SetZoom(float zoom);

  void SetCanvasSize(glm::vec2 size);
  void SetCameraMainSize(glm::vec2 size);

  glm::vec2 GetPosition();
  float GetZoom();

  float GetWidth();
  float GetHeight();

  glm::mat4 GetProjectionMatrix();

  glm::vec2 ScreenToWorld(glm::vec2);

 private:
  glm::vec4 GetProjectionParams();
  void RecalculateProjectionMatrix();

  glm::mat4 m_projectionMat;

  glm::vec2 m_canvasSize;          // size of ImGui canvas, used for aspect ratio calculation
  glm::vec2 m_cameraAspectedSize;  // this size is modified by aspect ratio and canvas size
  glm::vec2 m_cameraMainSize;      // this size will always be shown

  glm::vec2 m_position;
  float m_zoom;

  glm::vec2 m_lastEventMousePosition;
};
}  // namespace GLCore
