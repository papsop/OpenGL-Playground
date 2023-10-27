#include <GLCore/Utils/Camera.h>
#include <algorithm>

namespace GLCore {

I_Camera::I_Camera(E_CameraType type) : m_Type(type)
{
}

GLCore::E_CameraType I_Camera::GetCameraType()
{
  return m_Type;
}

glm::mat4 I_Camera::GetProjection()
{
  return m_projectionMatrix;
}

glm::vec3 I_Camera::GetPosition()
{
  return m_position;
}

glm::vec3 I_Camera::GetTarget()
{
  return m_target;
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
  val = std::max(0.1f, val);
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
