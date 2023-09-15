#pragma once
#include <glm/glm.hpp>

namespace GLCore {

class OrthographicCamera {
 public:
  OrthographicCamera(float left, float right, float bottom, float top);

  void SetProjection(float left, float right, float bottom, float top);
  void SetPosition(glm::vec3 position);

  glm::mat4 GetProjectionMatrix();

 private:
  glm::mat4 m_projectionMat;
};
}  // namespace GLCore
