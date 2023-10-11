#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Core/Events.h>
#include <GLCore/Utils/Shader.h>
#include <GLCore/Utils/Texture.h>

#include <GLSandbox/Utils/SandWorld.h>
#include <glm/vec4.hpp>

namespace GLSandbox {

class SandLayer : public GLCore::I_Layer {
 public:
  SandLayer() : I_Layer("Sand layer")
  {
  }

  void OnAttach() override;
  void OnDetach() override;

  void OnUpdate(GLCore::Timestep dt) override;
  void OnSandboxCanvasMouseEvent(const GLCore::E_SandboxCanvasMouseEvent& e);

 private:
  void UpdateSandWorld();

  static constexpr size_t m_pixelsWidth = 200;
  static constexpr size_t m_pixelsHeight = 200;
  unsigned char m_pixelsBuffer[m_pixelsWidth * m_pixelsHeight * 4];

  const float m_fixedUpdate = 0.0005f;
  float m_updateAccumulator = 0.0f;

  glm::vec2 m_center;
  glm::vec2 m_size;
  GLCore::Texture m_sandTexture;
  std::unique_ptr<SandWorld> m_sandWorld;

  Cell m_sandCell, m_waterCell;
};
}  // namespace GLSandbox
