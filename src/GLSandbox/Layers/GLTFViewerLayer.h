#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Core/Events.h>
#include <GLCore/Utils/Shader.h>

#include <GLSandbox/Utils/Model.h>

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
  bool m_ModelLoaded;
  tinygltf::Model m_Model;
  tinygltf::TinyGLTF m_Loader;

  Model m_ModelTest;
  unsigned int m_VAO;
  unsigned int m_VBO;
  unsigned int m_EBO;

  GLCore::Shader m_BasicShader;

  // render settings
  bool m_WireFrame = true;
  bool m_RotateCamera = false;
  float m_TotalTime = 0.0f;
};
}  // namespace GLSandbox
