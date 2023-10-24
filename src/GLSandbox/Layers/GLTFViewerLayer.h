#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Core/Events.h>
#include <GLCore/Utils/Shader.h>

#include <GLSandbox/gltf/tiny_gltf.h>
#include <string>

namespace GLSandbox {
class GLTFViewerLayer : public GLCore::I_Layer {
 public:
  GLTFViewerLayer() : I_Layer("GLTF Viewer", true)
  {
  }

  void OnAttach() override;
  void OnDetach() override;

  void OnUpdate(GLCore::Timestep dt) override;

  void OnImGuiUpdate(GLCore::Timestep dt) override;

 private:
  bool m_modelLoaded;
  tinygltf::Model m_model;
  tinygltf::TinyGLTF m_loader;

  unsigned int m_VAO;
  unsigned int m_VBO;
  unsigned int m_EBO;

  GLCore::Shader m_basicShader;

  // render settings
  bool m_wireFrame = true;
  bool m_rotateCamera = true;
  float m_totalTime = 0.0f;
};
}  // namespace GLSandbox
