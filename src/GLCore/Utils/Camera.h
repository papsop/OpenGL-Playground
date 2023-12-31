#pragma once
#include <GLCore/Core/Timestep.h>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>

namespace GLCore {
class CameraControlLayer;

enum class E_CameraType { NONE, ORTHOGRAPHIC, PERSPECTIVE };

class I_Camera {
 public:
  I_Camera(E_CameraType type);
  virtual ~I_Camera() = default;

  virtual glm::vec2 ScreenToWorld(glm::vec2 pos) = 0;

  E_CameraType GetCameraType();
  glm::mat4 GetProjection();
  glm::vec3 GetPosition();
  glm::vec3 GetTarget();
  glm::vec2 GetSize();
  float GetZoom();

  void SetPosition(glm::vec3 pos);
  void SetZoom(float val);
  void SetCanvasSize(glm::vec2 size);
  void SetCameraMainSize(glm::vec2 size);

 protected:
  virtual void RecalculateProjectionMatrix() = 0;
  E_CameraType m_Type;
  glm::mat4 m_projectionMatrix;
  glm::vec3 m_position;

  glm::vec2 m_canvasSize;          // size of ImGui canvas, used for aspect ratio calculation
  glm::vec2 m_cameraAspectedSize;  // this size is modified by aspect ratio and canvas size
  glm::vec2 m_cameraMainSize;      // this size will always be rendered
  glm::vec3 m_target;              // dynamic camera target, for now let's just keep it static
  float m_zoom;
};
}  // namespace GLCore
