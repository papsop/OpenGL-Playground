#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Core/Events.h>
#include <GLCore/Utils/Shader.h>

namespace GLSandbox {
enum class E_ParticleType {
  NONE,
  SAND,
  WATER,

  COUNT  // always last
};
struct Particle {
  E_ParticleType Type;
};

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
  static constexpr size_t m_pixelsWidth = 400;
  static constexpr size_t m_pixelsHeight = 400;
  unsigned char m_pixelsBuffer[m_pixelsWidth * m_pixelsHeight * 4];
  Particle m_particles[m_pixelsWidth * m_pixelsHeight];

  GLCore::Shader m_textureShader;

  unsigned int m_textureID;
  unsigned int m_quadVAO;
  unsigned int m_quadVBO;
};
}  // namespace GLSandbox
