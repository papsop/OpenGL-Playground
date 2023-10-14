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

}  // namespace GLCore
