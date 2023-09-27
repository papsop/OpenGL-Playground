#include <GLSandbox/Layers/SandLayer.h>
#include <GLCore/Core/Application.h>

#include <GLCore/Core/GLFWGlad.h>

namespace GLSandbox {

void SandLayer::OnAttach()
{
  REGISTER_EVENT_CALLBACK(GLCore::E_SandboxCanvasMouseEvent, this, &SandLayer::OnSandboxCanvasMouseEvent);

  m_textureShader.LoadShadersFromFiles("../assets/shaders/texShader.vert.glsl", "../assets/shaders/texShader.frag.glsl");

  // TEXTURE
  glGenTextures(1, &m_textureID);
  glBindTexture(GL_TEXTURE_2D, m_textureID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // size increase/decrease
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  // WRAPPING
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_pixelsWidth, m_pixelsHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_pixelsBuffer);
  glBindTexture(GL_TEXTURE_2D, 0);

  // QUAD
  float quadVertices[] = {-1.0f, 1.0f, 0.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f,
                          -1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  -1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f};

  glGenVertexArrays(1, &m_quadVAO);
  glGenBuffers(1, &m_quadVBO);
  glBindVertexArray(m_quadVAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

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

  glBindTexture(GL_TEXTURE_2D, m_textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_pixelsWidth, m_pixelsHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_pixelsBuffer);
  glBindTexture(GL_TEXTURE_2D, 0);

  m_textureShader.Use();
  m_textureShader.SetUniform("vProjectionMatrix", GLCore::Application::Instance().GetMainCamera()->GetProjectionMatrix());

  glBindVertexArray(m_quadVAO);
  glBindTexture(GL_TEXTURE_2D, m_textureID);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void SandLayer::OnSandboxCanvasMouseEvent(const GLCore::E_SandboxCanvasMouseEvent& e)
{
}

}  // namespace GLSandbox
