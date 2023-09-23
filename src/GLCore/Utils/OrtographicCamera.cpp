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

void OrthographicCamera::SetCanvasSize(GLsizei width, GLsizei height)
{
  m_canvasWidth = width;
  m_canvasHeight = height;
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

  glm::vec2 result = ((screenPos / glm::vec2{m_canvasWidth, m_canvasHeight}) * glm::vec2(2, 2)) - glm::vec2(1, 1);
  result.y *= -1.0;  // need to flip, so it corresponds to opengl world coords

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

void OrthographicCamera::RecalculateProjectionMatrix()
{
  CalculatedCameraData newData;
  newData.Borders[0] = m_left;
  newData.Borders[1] = m_right;
  newData.Borders[2] = m_bottom;
  newData.Borders[3] = m_top;
  newData.Position = m_position;
  newData.Zoom = m_zoom;

  if (newData == m_calculatedData) return;  // ignore, same data

  glm::vec3 positionVec3 = glm::vec3(m_position.x, m_position.y, -3.0f);
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), positionVec3);
  glm::mat4 viewMatrix = glm::inverse(transform);

  m_projectionMat = glm::ortho(m_left / m_zoom, m_right / m_zoom, m_bottom / m_zoom, m_top / m_zoom, -1000.0f, 1000.0f);
  m_projectionMat = m_projectionMat * viewMatrix;
  m_calculatedData = newData;
}
}  // namespace GLCore
