#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Core/Events.h>
#include <GLCore/Utils/Shader.h>
#include <GLCore/Utils/Texture.h>

#include <glm/vec4.hpp>

#include <TinyRenderer/Renderer.h>
#include <TinyRenderer/utils/Model.h>

namespace GLSandbox
{
class TinyRendererLayer : public GLCore::I_Layer
{
 public:
  TinyRendererLayer(bool enabled);

  void OnAttach() override;
  void OnDetach() override;

  void OnUpdate(GLCore::Timestep dt) override;

  void OnImGuiUpdate(GLCore::Timestep dt) override;

 private:
  std::shared_ptr<GLCore::Texture> m_Texture;
  std::shared_ptr<GLCore::TextureBuffer> m_TextureBuffer;

  tinyrenderer::Model m_Model;
  tinyrenderer::Renderer m_Renderer;
};
}  // namespace GLSandbox
