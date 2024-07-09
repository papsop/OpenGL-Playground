#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Core/Events.h>

namespace GLSandbox
{
class DrawingLayer : public GLCore::I_Layer
{
 public:
  DrawingLayer(bool enabled) : I_Layer("Drawing layer", enabled)
  {
  }

  void OnAttach() override;
  void OnDetach() override;

  void OnUpdate(GLCore::Timestep dt) override;
  void OnSandboxCanvasMouseEvent(const GLCore::E_SandboxCanvasMouseEvent& e);

 private:
  glm::vec2 m_lastPoint;
  // bool m_adding = false;
  std::vector<std::pair<glm::vec2, glm::vec2> > m_lines;  // for testing

  bool m_drawing = false;
  std::pair<glm::vec2, glm::vec2> m_linePreview;
};
}  // namespace GLSandbox
