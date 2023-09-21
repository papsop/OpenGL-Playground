#include <GLCore/Utils/OrtographicCamera.h>
#include <GLCore/Core/Application.h>

#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
namespace GLCore {

void OrthographicCamera::Create(float left, float right, float bottom, float top)
{
  SetProjection(left, right, bottom, top);
  m_data.Position = {0.0f, 0.0f};
  m_defaultData = m_data;

  REGISTER_EVENT_CALLBACK(SandboxCanvasEvent, this, &OrthographicCamera::OnSandboxCanvasResize);
  REGISTER_EVENT_CALLBACK(SandboxCanvasMouseEvent, this, &OrthographicCamera::OnSandboxCanvasMouseEvent);
}

void OrthographicCamera::SetPosition(glm::vec2 position)
{
  m_data.Position = position;
  RecalculateProjectionMatrix();
}

void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{
  m_data.Borders[0] = left;
  m_data.Borders[1] = right;
  m_data.Borders[2] = bottom;
  m_data.Borders[3] = top;
  RecalculateProjectionMatrix();
}

OrthographicCameraData OrthographicCamera::GetCameraData()
{
  return m_data;
}

void OrthographicCamera::SetCameraData(OrthographicCameraData data)
{
  m_data = data;
  RecalculateProjectionMatrix();
}

void OrthographicCamera::ResetToDefaultData()
{
  m_data = m_defaultData;
  RecalculateProjectionMatrix();
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
  auto& b = m_data.Borders;
  float width = abs(std::min(b[0], b[1]) - std::max(b[0], b[1]));
  float height = abs(std::min(b[2], b[3]) - std::max(b[2], b[3]));

  // map interval (-1;1) to (min_border, max_border)
  result.x *= (width - abs(std::min(b[0], b[1])));
  result.y *= (height - abs(std::min(b[2], b[3])));

  // move by camera position
  result += glm::vec2(m_data.Position.x, m_data.Position.y);
  return result;
}

void OrthographicCamera::OnSandboxCanvasResize(const SandboxCanvasEvent& event)
{
  if (event.Type == SandboxCanvasEvent::Resize) {
    m_canvasSize = event.Data.NewSize;
    LOG_INFO("received canvas resized event");
  }
}

void OrthographicCamera::OnSandboxCanvasMouseEvent(const SandboxCanvasMouseEvent& event)
{
  if (event.Type != SandboxCanvasMouseEvent::RightClickDown && event.Type != SandboxCanvasMouseEvent::RightClickPressed &&
      event.Type != SandboxCanvasMouseEvent::RightClickReleased)
    return;

  if (event.Type == SandboxCanvasMouseEvent::RightClickPressed || event.Type == SandboxCanvasMouseEvent::RightClickReleased) {
    // m_lastFrameMousePosition = ScreenToWorld(event.Position);
  }
  else {
    glm::vec2 mousePos = ScreenToWorld(event.Position);
    glm::vec2 offset = mousePos - m_lastEventMousePosition;
    m_data.Position -= offset;
    RecalculateProjectionMatrix();
  }
  // can't use "mousePos", have to recalculate, since we changed ProjectionMatrix
  m_lastEventMousePosition = ScreenToWorld(event.Position);
}

// TODO: compare old/new data, maybe we don't have to recalculate every frame
// cba right now
void OrthographicCamera::RecalculateProjectionMatrix()
{
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_data.GetPositionVec3());
  glm::mat4 viewMatrix = glm::inverse(transform);

  m_projectionMat = glm::ortho(m_data.Borders[0], m_data.Borders[1], m_data.Borders[1], m_data.Borders[2], -1000.0f, 1000.0f);
  m_projectionMat = m_projectionMat * viewMatrix;
}
}  // namespace GLCore
