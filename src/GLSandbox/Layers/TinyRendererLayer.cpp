#include <GLSandbox/Layers/TinyRendererLayer.h>
#include <GLCore/Core/Application.h>

#include <GLCore/Core/GLFWGlad.h>
#include <GLCore/Utils/Log.h>

#include <TinyRenderer/Renderer.h>

#include <imgui.h>

namespace GLSandbox
{
TinyRendererLayer::TinyRendererLayer(bool enabled) : I_Layer("Tiny Renderer", enabled)
{
  m_Texture = std::make_shared<GLCore::Texture>();
  m_TextureBuffer = std::make_shared<GLCore::TextureBuffer>(200, 200);
}

void TinyRendererLayer::OnAttach()
{
  m_Model.LoadOBJModel("../assets/models/african_head.obj");
}

void TinyRendererLayer::OnDetach()
{
}

void TinyRendererLayer::OnUpdate(GLCore::Timestep dt)
{
  if (!m_Model.IsLoaded()) return;

  m_Renderer.BindTextureBuffer(m_TextureBuffer);

  // m_Renderer.DrawModelWireframe({400, 400}, m_Model);

  glm::vec2 t0[3] = {glm::vec2(10, 70), glm::vec2(50, 160), glm::vec2(70, 80)};
  glm::vec2 t1[3] = {glm::vec2(180, 50), glm::vec2(150, 1), glm::vec2(70, 180)};
  glm::vec2 t2[3] = {glm::vec2(180, 150), glm::vec2(120, 160), glm::vec2(130, 180)};

  m_Renderer.DrawTriangle(t0[0], t0[1], t0[2], GLCore::ColorLibrary::Red);
  m_Renderer.DrawTriangle(t1[0], t1[1], t1[2], GLCore::ColorLibrary::White);
  m_Renderer.DrawTriangle(t2[0], t2[1], t2[2], GLCore::ColorLibrary::Green);

  // Draw texture
  m_Texture->SetImageData(*m_TextureBuffer);
  GLCore::Application::Instance().GetRenderer()->DrawQuad({0.0f, 0.0f}, {10.0f, 10.0f}, m_Texture.get());
}

void TinyRendererLayer::OnImGuiUpdate(GLCore::Timestep dt)
{
}

}  // namespace GLSandbox
