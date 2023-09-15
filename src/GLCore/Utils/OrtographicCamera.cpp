#include <GLCore/Utils/OrtographicCamera.h>
#include <glm/gtc/matrix_transform.hpp>

namespace GLCore {

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
{
  SetProjection(left, right, bottom, top);
}

void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{
  m_projectionMat = glm::ortho(left, right, bottom, top, -100.0f, 100.0f);
  // glm::translate(m_projectionMat, {0.0f, 0.0f, -3.0f});
}

void OrthographicCamera::SetPosition(glm::vec3 position)
{
}

glm::mat4 OrthographicCamera::GetProjectionMatrix()
{
  return m_projectionMat;
}
}  // namespace GLCore
