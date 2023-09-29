#include <GLSandbox/Layers/SandLayer.h>
#include <GLCore/Core/Application.h>

#include <GLCore/Core/GLFWGlad.h>

namespace GLSandbox {

void SandLayer::OnAttach()
{
  REGISTER_EVENT_CALLBACK(GLCore::E_SandboxCanvasMouseEvent, this, &SandLayer::OnSandboxCanvasMouseEvent);

  for (int i = 0; i < m_pixelsWidth * m_pixelsHeight; i++) {
    if (i % 50 == 0) {
      m_particles[i].Type = E_ParticleType::SAND;
    }
    if (i % 70 == 0) {
      m_particles[i].Type = E_ParticleType::WATER;
    }
    else {
      m_particles[i].Type = E_ParticleType::NONE;
    }
  }

  m_center = {0.0f, 0.0f};
  m_size = {8.0f, 8.0f};
}

void SandLayer::OnDetach()
{
  UNREGISTER_EVENT_CALLBACK(GLCore::E_SandboxCanvasMouseEvent, this);
}

void SandLayer::OnUpdate(GLCore::Timestep dt)
{
  Particle* nextParticle = &m_particles[0];
  unsigned char* nextPixel = &m_pixelsBuffer[0];
  for (int i = 0; i < m_pixelsWidth * m_pixelsHeight; i++) {
    unsigned char channel;
    switch (nextParticle->Type) {
      case (E_ParticleType::NONE):
        channel = static_cast<unsigned char>(0);
        break;
      case (E_ParticleType::SAND):
        channel = static_cast<unsigned char>(255);
        break;
      case (E_ParticleType::WATER):
        channel = static_cast<unsigned char>(125);
        break;
      default:
        break;
    }

    *nextPixel = channel;
    ++nextPixel;
    *nextPixel = channel;
    ++nextPixel;
    *nextPixel = channel;
    ++nextPixel;
    *nextPixel = 255;
    ++nextPixel;
    ++nextParticle;
  }

  m_sandTexture.SetImageData(m_pixelsWidth, m_pixelsHeight, m_pixelsBuffer);
  GLCore::Application::Instance().GetRenderer()->DrawQuad(m_center, m_size, &m_sandTexture);
}

void SandLayer::OnSandboxCanvasMouseEvent(const GLCore::E_SandboxCanvasMouseEvent& e)
{
  //   if (e.Type == GLCore::E_SandboxCanvasMouseEvent::LeftClickPressed) {
  //     m_center = GLCore::Application::Instance().GetMainCamera()->ScreenToWorld(e.Position);
  //   }
}

}  // namespace GLSandbox
