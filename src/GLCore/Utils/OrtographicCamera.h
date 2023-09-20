#pragma once
#include <GLCore/Core/Events.h>

#include <glm/glm.hpp>

namespace GLCore {

struct OrthographicCameraData {
  glm::vec4 Borders;  // left, right, bottom, top
  glm::vec2 Position;
  glm::vec3 GetPositionVec3()
  {
    return glm::vec3(Position.x, Position.y, -3.0f);  // meh
  }
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
  void Create(float left, float right, float bottom, float top);

  void SetPosition(glm::vec2 position);
  void SetProjection(float left, float right, float bottom, float top);

  OrthographicCameraData GetCameraData();
  void SetCameraData(OrthographicCameraData data);
  void ResetToDefaultData();

  glm::mat4 GetProjectionMatrix();

  glm::vec2 ScreenToWorld(glm::vec2);

  void OnSandboxCanvasResize(const SandboxCanvasEvent& event);
  void OnSandboxCanvasMouseEvent(const SandboxCanvasMouseEvent& event);

 private:
  void RecalculateProjectionMatrix();

  OrthographicCameraData m_defaultData;
  OrthographicCameraData m_data;
  glm::mat4 m_projectionMat;
  glm::vec2 m_canvasSize;
  float m_sensitivity = 0.05f;
};
}  // namespace GLCore
