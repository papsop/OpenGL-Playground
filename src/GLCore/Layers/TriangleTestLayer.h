#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Utils/Shader.h>

namespace GLCore {
class TriangleTestLayer : public I_Layer {
 public:
  TriangleTestLayer() : I_Layer("Triangle test"){};
  void OnUpdate(Timestep dt) override;

  void OnAttach() override;

 private:
  Shader m_shader;
  unsigned int m_VAO;
};
}  // namespace GLCore
