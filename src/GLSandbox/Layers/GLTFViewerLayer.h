#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Core/Events.h>
#include <GLCore/Utils/Shader.h>

#include <GLSandbox/Utils/Model.h>

#include <GLSandbox/gltf/tiny_gltf.h>
#include <string>

namespace GLSandbox
{
class GLTFViewerLayer : public GLCore::I_Layer
{
 public:
  GLTFViewerLayer(bool enabled) : I_Layer("GLTF Viewer", enabled)
  {
  }

  void OnAttach() override;

  void OnUpdate(GLCore::Timestep dt) override;

  void OnImGuiUpdate(GLCore::Timestep dt) override;

 private:
  Model m_Model;

  // render settings
  bool m_WireFrame = true;
  bool m_RotateCamera = false;
  float m_TotalTime = 0.0f;
};
}  // namespace GLSandbox
