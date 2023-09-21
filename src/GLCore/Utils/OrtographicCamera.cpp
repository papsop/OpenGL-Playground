#include <GLCore/Utils/OrtographicCamera.h>
#include <GLCore/Core/Application.h>

#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
namespace GLCore {

void OrthographicCamera::Create(float left, float right, float bottom, float top)
{
  SetProjection(left, right, bottom, top);
  SetZoom(1.0f);
}

void OrthographicCamera::SetPosition(glm::vec2 position)
{
  m_position = position;
  RecalculateProjectionMatrix();
}

void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{
  m_left = left;
  m_right = right;
  m_bottom = bottom;
  m_top = top;
  RecalculateProjectionMatrix();
}

void OrthographicCamera::SetZoom(float zoom)
{
  m_zoom = zoom;
  RecalculateProjectionMatrix();
}

void OrthographicCamera::SetCanvasSize(glm::vec2 size)
{
  m_canvasSize = size;
  LOG_INFO("Canvas resized");
  // no need to recalculate, this only affects ScreenToWorld()
}

glm::vec2 OrthographicCamera::GetPosition()
{
  return m_position;
}

float OrthographicCamera::GetZoom()
{
  return m_zoom;
}

glm::mat4 OrthographicCamera::GetProjectionMatrix()
{
  return m_projectionMat;
}

glm::vec2 OrthographicCamera::ScreenToWorld(glm::vec2 screenPos)
{
  // screen space (-1;1), [0,0] is middle of the screen
  float leftZ = m_left / m_zoom;
  float rightZ = m_right / m_zoom;
  float bottomZ = m_bottom / m_zoom;
  float topZ = m_top / m_zoom;

  glm::vec2 result = ((screenPos / m_canvasSize) * glm::vec2(2, 2)) - glm::vec2(1, 1);

  // get lengths of camera borders
  float width = abs(std::min(leftZ, rightZ) - std::max(leftZ, rightZ));
  float height = abs(std::min(bottomZ, topZ) - std::max(bottomZ, topZ));

  // map interval (-1;1) to (min_border, max_border)
  result.x *= (width - abs(std::min(leftZ, rightZ)));
  result.y *= (height - abs(std::min(bottomZ, topZ)));

  // move by camera position
  result += m_position;
  return result;
}

// TODO: compare old/new data, maybe we don't have to recalculate every frame
// cba right now
void OrthographicCamera::RecalculateProjectionMatrix()
{
  glm::vec3 positionVec3 = glm::vec3(m_position.x, m_position.y, -3.0f);
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), positionVec3);
  glm::mat4 viewMatrix = glm::inverse(transform);

  m_projectionMat = glm::ortho(m_left / m_zoom, m_right / m_zoom, m_bottom / m_zoom, m_top / m_zoom, -1000.0f, 1000.0f);
  m_projectionMat = m_projectionMat * viewMatrix;
}
}  // namespace GLCore
