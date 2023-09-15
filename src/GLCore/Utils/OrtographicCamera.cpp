#include <GLCore/Utils/OrtographicCamera.h>
#include <glm/gtc/matrix_transform.hpp>

namespace GLCore {

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
{
  SetProjection(left, right, bottom, top);
  m_data.Position = {0.0f, 0.0f, -0.3f};
  m_defaultData = m_data;
}

void OrthographicCamera::SetPosition(glm::vec3 position)
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

// TODO: compare old/new data, maybe we don't have to recalculate every frame
// cba right now
void OrthographicCamera::RecalculateProjectionMatrix()
{
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_data.Position);
  glm::mat4 viewMatrix = glm::inverse(transform);

  m_projectionMat = glm::ortho(m_data.Borders[0], m_data.Borders[1], m_data.Borders[1], m_data.Borders[2], -1000.0f, 1000.0f);
  m_projectionMat = m_projectionMat * viewMatrix;
}
}  // namespace GLCore
