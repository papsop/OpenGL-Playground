#pragma once
#include <GLCore/Core/Layer.h>

namespace GLCore {
class TriangleTestLayer : public I_Layer {
 public:
  TriangleTestLayer() : I_Layer("Triangle test"){};
  void OnUpdate(Timestep dt) override;

  void OnAttach() override;

 private:
  unsigned int m_shaderProgram;
  unsigned int m_VAO;
};
}  // namespace GLCore
