#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Core/Events.h>

namespace GLSandbox {
class TestLayer : public GLCore::I_Layer {
 public:
  TestLayer() : I_Layer("Sandbox test layer")
  {
  }

  void OnAttach() override;
  void OnDetach() override;

  void OnUpdate(GLCore::Timestep dt) override;
  void OnSandboxCanvasMouseEvent(const GLCore::SandboxCanvasMouseEvent& e);

 private:
  glm::vec2 m_lastPoint;
  bool m_adding = false;
  std::vector<std::pair<glm::vec2, glm::vec2> > m_lines;  // for testing
};
}  // namespace GLSandbox
