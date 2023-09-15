#pragma once
#include <glm/glm.hpp>

namespace GLCore {

struct OrthographicCameraData {
  glm::vec4 Borders;  // left, right, bottom, top
  glm::vec3 Position;
  OrthographicCameraData() = default;
  OrthographicCameraData(glm::vec4 b, glm::vec3 p) : Borders(b), Position(p){};
  OrthographicCameraData(const OrthographicCameraData& other) : Borders(other.Borders), Position(other.Position){};

  bool operator==(const OrthographicCameraData& other)
  {
    return other.Borders == Borders && other.Position == Position;
  }

  bool operator!=(const OrthographicCameraData& other)
  {
    return !(*this == other);
  }
};

class OrthographicCamera {
 public:
  OrthographicCamera(float left, float right, float bottom, float top);

  void SetPosition(glm::vec3 position);
  void SetProjection(float left, float right, float bottom, float top);

  OrthographicCameraData GetCameraData();
  void SetCameraData(OrthographicCameraData data);
  void ResetToDefaultData();

  glm::mat4 GetProjectionMatrix();

 private:
  void RecalculateProjectionMatrix();

  OrthographicCameraData m_defaultData;
  OrthographicCameraData m_data;
  glm::mat4 m_projectionMat;
};
}  // namespace GLCore
