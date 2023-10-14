#include <GLCore/Utils/PerspectiveCamera.h>
#include <glm/ext.hpp>

namespace GLCore {

PerspectiveCamera::PerspectiveCamera(glm::vec3 pos)
{
  m_position = pos;
  RecalculateProjectionMatrix();
}

glm::vec2 PerspectiveCamera::ScreenToWorld(glm::vec2 pos)
{
  return {0, 0};
}

void PerspectiveCamera::RecalculateProjectionMatrix()
{
  m_cameraTarget = glm::vec3(0, 0, 0);
  m_cameraDirection = glm::normalize(m_position - m_cameraTarget);

  glm::vec3 worldUp = glm::vec3(0, 1, 0);
  m_cameraRight = glm::normalize(glm::cross(worldUp, m_cameraDirection));

  m_cameraUp = glm::normalize(glm::cross(m_cameraDirection, m_cameraRight));

  m_viewMatrix = glm::lookAt(m_position, glm::vec3(0, 0, 0), m_cameraUp);
}
}  // namespace GLCore
