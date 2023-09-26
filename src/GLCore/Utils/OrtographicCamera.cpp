#include <GLCore/Utils/OrtographicCamera.h>
#include <GLCore/Core/Application.h>

#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

namespace GLCore {

void OrthographicCamera::Create(glm::vec2 size, glm::vec2 position)
{
  m_cameraSize = size;
  m_zoom = 1.0f;
  m_position = position;
  RecalculateProjectionMatrix();
}

void OrthographicCamera::SetPosition(glm::vec2 position)
{
  if (m_position == position) return;

  m_position = position;
  RecalculateProjectionMatrix();
}

void OrthographicCamera::SetZoom(float zoom)
{
  if (m_zoom == zoom) return;

  m_zoom = zoom;
  RecalculateProjectionMatrix();
}

void OrthographicCamera::SetCanvasSize(glm::vec2 size)
{
  if (m_canvasSize == size) return;

  m_canvasSize = size;
  RecalculateProjectionMatrix();
}

void OrthographicCamera::SetCameraSize(glm::vec2 size)
{
  if (m_cameraSize == size) return;

  m_cameraSize = size;
  RecalculateProjectionMatrix();
}

glm::vec2 OrthographicCamera::GetPosition()
{
  return m_position;
}

float OrthographicCamera::GetZoom()
{
  return m_zoom;
}

float OrthographicCamera::GetWidth()
{
  // float left = (m_cameraSize.x / -2.0f) / m_zoom;
  // float right = (m_cameraSize.x / 2.0f) / m_zoom;
  // return abs(left - right);
  return m_aspectedCameraSize.x;
}

float OrthographicCamera::GetHeight()
{
  // float bottom = (m_cameraSize.y / -2.0f) / m_zoom;
  // float top = (m_cameraSize.y / 2.0f) / m_zoom;
  // return abs(bottom - top);
  return m_aspectedCameraSize.y;
}

glm::mat4 OrthographicCamera::GetProjectionMatrix()
{
  return m_projectionMat;
}

glm::vec2 OrthographicCamera::ScreenToWorld(glm::vec2 screenPos)
{
  glm::vec2 result = ((screenPos / m_canvasSize) * glm::vec2(2, 2)) - glm::vec2(1, 1);
  result.y *= -1.0;  // need to flip, so it corresponds to opengl world coords

  // get lengths of camera borders
  float width = GetWidth() / m_zoom;
  float height = GetHeight() / m_zoom;

  // map interval (-1;1) to (min_border, max_border)
  result.x *= (width - width / 2.0f);
  result.y *= (height - height / 2.0f);

  // move by camera position
  result += m_position;
  return result;
}

glm::vec4 OrthographicCamera::GetProjectionParams()
{
  glm::vec4 params;
  params[0] = (m_cameraSize.x / -2.0f) / m_zoom;
  params[1] = (m_cameraSize.x / 2.0f) / m_zoom;
  params[2] = (m_cameraSize.y / -2.0f) / m_zoom;
  params[3] = (m_cameraSize.y / 2.0f) / m_zoom;
  return params;
}

void OrthographicCamera::RecalculateProjectionMatrix()
{
  glm::vec4 projectParams = GetProjectionParams();

  glm::vec3 positionVec3 = glm::vec3(m_position.x, m_position.y, -3.0f);
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), positionVec3);
  glm::mat4 viewMatrix = glm::inverse(transform);

  float canvasAspect = m_canvasSize.x / m_canvasSize.y;
  float cameraAspect = m_cameraSize.x / m_cameraSize.y;

  // LOG_INFO("canvas: {0}, camera: {1}", canvasAspect, cameraAspect);
  m_aspectedCameraSize = m_cameraSize;
  if (canvasAspect > cameraAspect) {
    float ratio = canvasAspect / cameraAspect;
    m_projectionMat = glm::ortho(ratio * projectParams[0], ratio * projectParams[1], projectParams[2], projectParams[3], -1000.0f, 1000.0f);
    m_aspectedCameraSize.x *= ratio;
  }
  else {
    float ratio = cameraAspect / canvasAspect;
    m_projectionMat = glm::ortho(projectParams[0], projectParams[1], ratio * projectParams[2], ratio * projectParams[3], -1000.0f, 1000.0f);
    m_aspectedCameraSize.y *= ratio;
  }
  m_projectionMat = m_projectionMat * viewMatrix;
}
}  // namespace GLCore
