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
  m_TextureBuffer = std::make_shared<GLCore::TextureBuffer>(400, 400);
}

void TinyRendererLayer::OnAttach()
{
}

void TinyRendererLayer::OnDetach()
{
}

void TinyRendererLayer::OnUpdate(GLCore::Timestep dt)
{
  m_Renderer.BindTextureBuffer(m_TextureBuffer);
  m_Renderer.Line2D({0.0f, 0.0f}, {100.0f, 100.0f}, GLCore::ColorLibrary::White);
  m_Renderer.Line2D({100.0f, 0.0f}, {100.0f, 100.0f}, GLCore::ColorLibrary::White);
  m_Renderer.Line2D({0.0f, 100.0f}, {100.0f, 100.0f}, GLCore::ColorLibrary::Green);
  m_Renderer.Line2D({50.0f, 50.0f}, {50.0f, 0.0f}, GLCore::ColorLibrary::Blue);

  m_Texture->SetImageData(*m_TextureBuffer);
  GLCore::Application::Instance().GetRenderer()->DrawQuad({0.0f, 0.0f}, {10.0f, 10.0f}, m_Texture.get());
}

void TinyRendererLayer::OnImGuiUpdate(GLCore::Timestep dt)
{
}

}  // namespace GLSandbox
