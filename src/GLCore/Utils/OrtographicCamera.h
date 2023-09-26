#pragma once
#include <GLCore/Core/Events.h>

#include <glm/glm.hpp>

namespace GLCore {

// struct OrtographicProjectionParams {
//   float Left;
//   float Right;
//   float Bottom;
//   float Top;
//
//   float Zoom;
//   glm::vec2 Position;
//
//   OrtographicProjectionParams() = default;
//
//   OrtographicProjectionParams(float left, float right, float bottom, float top)
//       : Left(left), Right(right), Bottom(bottom), Top(top), Zoom(1.0f), Position(0.0f, 0.0f)
//   {
//   }
//
//   OrtographicProjectionParams(const OrtographicProjectionParams& o) = default;
//
//   bool operator==(const OrtographicProjectionParams& o)
//   {
//     return (Left == o.Left && Right == o.Right && Bottom == o.Bottom && Top == o.Top && Zoom == o.Zoom && Position == o.Position);
//   }
// };

class OrthographicCamera {
 public:
  OrthographicCamera() = default;
  ~OrthographicCamera() = default;

  void Create(glm::vec2 size, glm::vec2 position);

  void SetPosition(glm::vec2 position);
  void SetZoom(float zoom);

  void SetCanvasSize(glm::vec2 size);
  void SetCameraSize(glm::vec2 size);

  glm::vec2 GetPosition();
  float GetZoom();

  float GetWidth();
  float GetHeight();

  glm::mat4 GetProjectionMatrix();

  glm::vec2 ScreenToWorld(glm::vec2);

 private:
  glm::vec4 GetProjectionParams();
  void RecalculateProjectionMatrix();

  glm::mat4 m_projectionMat;

  glm::vec2 m_canvasSize;
  glm::vec2 m_aspectedCameraSize;
  glm::vec2 m_cameraSize;

  glm::vec2 m_position;
  float m_zoom;

  glm::vec2 m_lastEventMousePosition;
};
}  // namespace GLCore
