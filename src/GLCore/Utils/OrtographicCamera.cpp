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
  glm::vec2 result = ((screenPos / m_canvasSize) * glm::vec2(2, 2)) - glm::vec2(1, 1);

  // get lengths of camera borders
  float width = abs(std::min(m_left, m_right) - std::max(m_left, m_right));
  float height = abs(std::min(m_bottom, m_top) - std::max(m_bottom, m_top));

  // map interval (-1;1) to (min_border, max_border)
  result.x *= (width - abs(std::min(m_left, m_right)));
  result.y *= (height - abs(std::min(m_bottom, m_top)));

  // move by camera position
  result += m_position;
  return result;
}

void OrthographicCamera::OnSandboxCanvasResize(const SandboxCanvasEvent& event)
{
  //   if (event.Type == SandboxCanvasEvent::Resize) {
  //     m_canvasSize = event.Data.NewSize;
  //     LOG_INFO("received canvas resized event");
  //   }
}

void OrthographicCamera::OnSandboxCanvasMouseEvent(const SandboxCanvasMouseEvent& event)
{
  //   if (event.Type != SandboxCanvasMouseEvent::RightClickDown && event.Type != SandboxCanvasMouseEvent::RightClickPressed &&
  //       event.Type != SandboxCanvasMouseEvent::RightClickReleased)
  //     return;
  //
  //   if (event.Type == SandboxCanvasMouseEvent::RightClickPressed || event.Type == SandboxCanvasMouseEvent::RightClickReleased) {
  //     // m_lastFrameMousePosition = ScreenToWorld(event.Position);
  //   }
  //   else {
  //     glm::vec2 mousePos = ScreenToWorld(event.Position);
  //     glm::vec2 offset = mousePos - m_lastEventMousePosition;
  //     m_position -= offset;
  //     RecalculateProjectionMatrix();
  //   }
  //   // can't use "mousePos", have to recalculate, since we changed ProjectionMatrix
  //   m_lastEventMousePosition = ScreenToWorld(event.Position);
}

// TODO: compare old/new data, maybe we don't have to recalculate every frame
// cba right now
void OrthographicCamera::RecalculateProjectionMatrix()
{
  glm::vec3 positionVec3 = glm::vec3(m_position.x, m_position.y, -3.0f);
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), positionVec3);
  glm::mat4 viewMatrix = glm::inverse(transform);

  m_projectionMat = glm::ortho(m_left, m_right, m_bottom, m_top, -1000.0f, 1000.0f);
  m_projectionMat = m_projectionMat * viewMatrix;
}
}  // namespace GLCore
