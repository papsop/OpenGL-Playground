#include <GLCore/Utils/Camera.h>

namespace GLCore {
glm::mat4 I_Camera::GetProjection()
{
  return m_projectionMatrix;
}

glm::vec2 I_Camera::GetPosition()
{
  return m_position;
}

glm::vec2 I_Camera::GetSize()
{
  return m_cameraAspectedSize;
}

float I_Camera::GetZoom()
{
  return m_zoom;
}

void I_Camera::SetPosition(glm::vec3 pos)
{
  if (m_position == pos) return;

  m_position = pos;
  RecalculateProjectionMatrix();
}

void I_Camera::SetZoom(float val)
{
  if (m_zoom == val) return;

  m_zoom = val;
  RecalculateProjectionMatrix();
}

void I_Camera::SetCanvasSize(glm::vec2 size)
{
  if (m_canvasSize == size) return;

  m_canvasSize = size;
  RecalculateProjectionMatrix();
}

void I_Camera::SetCameraMainSize(glm::vec2 size)
{
  if (m_cameraMainSize == size) return;

  m_cameraMainSize = size;
  RecalculateProjectionMatrix();
}

}  // namespace GLCore
