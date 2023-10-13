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
  m_position = pos;
  RecalculateProjectionMatrix();
}

void I_Camera::SetZoom(float val)
{
  m_zoom = val;
  RecalculateProjectionMatrix();
}

}  // namespace GLCore
