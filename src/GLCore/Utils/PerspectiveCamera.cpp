#include <GLCore/Utils/PerspectiveCamera.h>
#include <algorithm>
#include <glm/ext.hpp>

namespace GLCore {

PerspectiveCamera::PerspectiveCamera(glm::vec3 pos)
{
  m_position = pos;
  m_canvasSize = {800, 600};
  m_cameraMainSize = {800, 600};
  m_zoom = 1.0f;
  RecalculateProjectionMatrix();
}

glm::vec2 PerspectiveCamera::ScreenToWorld(glm::vec2 pos)
{
  return {0, 0};
}

void PerspectiveCamera::RecalculateProjectionMatrix()
{
  // View matrix
  // m_target = m_position + glm::vec3(0, 0, -m_position.z - 1);  // target always in front of the camera
  m_target = glm::vec3(0, 0, 0);
  glm::vec3 dir = glm::normalize(m_position - m_target);

  glm::vec3 worldUp = glm::vec3(0, 1, 0);
  glm::vec3 right = glm::normalize(glm::cross(worldUp, dir));

  glm::vec3 up = glm::normalize(glm::cross(dir, right));

  glm::mat4 viewMatrix = glm::lookAt(m_position, m_target, up);

  // Projection matrix
  float canvasAspect = m_canvasSize.x / m_canvasSize.y;
  float cameraAspect = m_cameraMainSize.x / m_cameraMainSize.y;
  m_projectionMatrix = glm::perspective(glm::radians(45.0f / m_zoom), canvasAspect, 0.1f, 1000.0f);

  m_projectionMatrix = m_projectionMatrix * viewMatrix;
}
}  // namespace GLCore
