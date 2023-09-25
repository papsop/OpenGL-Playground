#pragma once
#include <GLCore/Core/Events.h>

#include <glm/glm.hpp>

namespace GLCore {

struct OrtographicProjectionParams {
  float Left;
  float Right;
  float Bottom;
  float Top;

  float Zoom;
  glm::vec2 Position;

  OrtographicProjectionParams() = default;

  OrtographicProjectionParams(float left, float right, float bottom, float top)
      : Left(left), Right(right), Bottom(bottom), Top(top), Zoom(1.0f), Position(0.0f, 0.0f)
  {
  }

  OrtographicProjectionParams(const OrtographicProjectionParams& o) = default;

  bool operator==(const OrtographicProjectionParams& o)
  {
    return (Left == o.Left && Right == o.Right && Bottom == o.Bottom && Top == o.Top && Zoom == o.Zoom && Position == o.Position);
  }
};

class OrthographicCamera {
 public:
  OrthographicCamera() = default;
  ~OrthographicCamera() = default;

  void Create(OrtographicProjectionParams params);

  void SetPosition(glm::vec2 position);
  void SetProjection(OrtographicProjectionParams params);
  void SetZoom(float zoom);
  void SetCanvasSize(int width, int height);

  glm::vec2 GetPosition();
  float GetZoom();
  OrtographicProjectionParams GetCameraParams();
  float GetCameraWidth();
  float GetCameraHeight();

  glm::mat4 GetProjectionMatrix();

  glm::vec2 ScreenToWorld(glm::vec2);

 private:
  void RecalculateProjectionMatrix();

  OrtographicProjectionParams m_params;
  glm::mat4 m_projectionMat;
  int m_canvasWidth;
  int m_canvasHeight;

  glm::vec2 m_position;
  float m_zoom;

  glm::vec2 m_lastEventMousePosition;
};
}  // namespace GLCore
