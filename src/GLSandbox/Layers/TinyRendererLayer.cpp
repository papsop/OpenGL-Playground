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
  m_TextureBuffer = std::make_shared<GLCore::TextureBuffer>(1000, 1000);
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

  // Render model
  for (size_t i = 0; i < m_Model.FacesSize(); i++)
  {
    std::vector<int> face = m_Model.Face(i);
    for (size_t j = 0; j < 3; j++)
    {
      // Get 3d points for given triangle face
      glm::vec3 v0 = m_Model.Vertex(face[j]);
      glm::vec3 v1 = m_Model.Vertex(face[(j + 1) % 3]);

      // Remap these points to 2d texture coords
      float width = m_TextureBuffer->GetWidth();
      float height = m_TextureBuffer->GetHeight();
      glm::vec2 p0 = {(v0.x + 1.) * width / 2., (v0.y + 1) * height / 2.};
      glm::vec2 p1 = {(v1.x + 1.) * width / 2., (v1.y + 1) * height / 2.};

      // draw line
      m_Renderer.Line2D(p0, p1, GLCore::ColorLibrary::White);
    }
  }

  // Draw texture
  m_Texture->SetImageData(*m_TextureBuffer);
  GLCore::Application::Instance().GetRenderer()->DrawQuad({0.0f, 0.0f}, {10.0f, 10.0f}, m_Texture.get());
}

void TinyRendererLayer::OnImGuiUpdate(GLCore::Timestep dt)
{
}

}  // namespace GLSandbox
