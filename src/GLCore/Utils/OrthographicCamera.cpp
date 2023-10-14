#include <GLCore/Utils/OrthographicCamera.h>
#include <GLCore/Core/Application.h>

#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

namespace GLCore {

OrthographicCamera::OrthographicCamera(glm::vec2 size, glm::vec2 position)
{
  m_cameraMainSize = size;
  m_zoom = 1.0f;
  m_position = glm::vec3(position.x, position.y, -3.0f);
  RecalculateProjectionMatrix();
}

glm::vec2 OrthographicCamera::ScreenToWorld(glm::vec2 screenPos)
{
  glm::vec2 result = ((screenPos / m_canvasSize) * glm::vec2(2, 2)) - glm::vec2(1, 1);
  result.y *= -1.0;  // need to flip, so it corresponds to opengl world coords

  // get lengths of camera borders
  auto size = GetSize() / m_zoom;

  // map interval (-1;1) to (min_border, max_border)
  result.x *= (size.x - size.x / 2.0f);
  result.y *= (size.y - size.y / 2.0f);

  // move by camera position
  GL_TODO("This should somehow support Vec3 position as well");
  result += glm::vec2(m_position.x, m_position.y);
  return result;
}

glm::vec4 OrthographicCamera::GetProjectionParams()
{
  glm::vec4 params;
  params[0] = (m_cameraMainSize.x / -2.0f) / m_zoom;
  params[1] = (m_cameraMainSize.x / 2.0f) / m_zoom;
  params[2] = (m_cameraMainSize.y / -2.0f) / m_zoom;
  params[3] = (m_cameraMainSize.y / 2.0f) / m_zoom;
  return params;
}

void OrthographicCamera::RecalculateProjectionMatrix()
{
  glm::vec4 projectParams = GetProjectionParams();

  glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position);
  glm::mat4 viewMatrix = glm::inverse(transform);

  float canvasAspect = m_canvasSize.x / m_canvasSize.y;
  float cameraAspect = m_cameraMainSize.x / m_cameraMainSize.y;

  // LOG_INFO("canvas: {0}, camera: {1}", canvasAspect, cameraAspect);
  m_cameraAspectedSize = m_cameraMainSize;
  if (canvasAspect > cameraAspect) {
    float ratio = canvasAspect / cameraAspect;
    m_projectionMatrix = glm::ortho(ratio * projectParams[0], ratio * projectParams[1], projectParams[2], projectParams[3], -1000.0f, 1000.0f);
    m_cameraAspectedSize.x *= ratio;
  }
  else {
    float ratio = cameraAspect / canvasAspect;
    m_projectionMatrix = glm::ortho(projectParams[0], projectParams[1], ratio * projectParams[2], ratio * projectParams[3], -1000.0f, 1000.0f);
    m_cameraAspectedSize.y *= ratio;
  }
  m_projectionMatrix = m_projectionMatrix * viewMatrix;
}
}  // namespace GLCore
