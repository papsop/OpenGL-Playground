#pragma once
#include <GLCore/Core/Events.h>

#include <glm/glm.hpp>

namespace GLCore {

class OrthographicCamera {
 public:
  void Create(float left, float right, float bottom, float top);

  void SetPosition(glm::vec2 position);
  void SetProjection(float left, float right, float bottom, float top);
  void SetZoom(float zoom);

  glm::vec2 GetPosition();
  float GetZoom();

  glm::mat4 GetProjectionMatrix();

  glm::vec2 ScreenToWorld(glm::vec2);

  void OnSandboxCanvasResize(const SandboxCanvasEvent& event);
  void OnSandboxCanvasMouseEvent(const SandboxCanvasMouseEvent& event);

 private:
  void RecalculateProjectionMatrix();

  glm::mat4 m_projectionMat;
  glm::vec2 m_canvasSize;

  float m_left;
  float m_right;
  float m_bottom;
  float m_top;

  glm::vec2 m_position;
  float m_zoom;

  glm::vec2 m_lastEventMousePosition;
};
}  // namespace GLCore
