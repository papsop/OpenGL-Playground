#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Utils/Shader.h>

namespace GLCore {
class TriangleTestLayer : public I_Layer {
 public:
  TriangleTestLayer() : I_Layer("Triangle test"){};
  void OnAttach() override;
  void OnDetach() override;

  void OnUpdate(Timestep dt) override;
  void OnImGuiUpdate(Timestep dt) override;

 private:
  Shader m_shader;
  unsigned int m_VAO;
  unsigned int m_FBO;
  unsigned int m_RBO;
  unsigned int m_texture;
};
}  // namespace GLCore
