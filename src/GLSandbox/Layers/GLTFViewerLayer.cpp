#include <GLSandbox/Layers/GLTFViewerLayer.h>

#include <GLCore/Core/Application.h>
#include <GLCore/Core/GLFWGlad.h>

#include <iostream>
#include <imgui.h>

namespace GLSandbox {

void GLTFViewerLayer::OnAttach()
{
  GL_TODO("Parse tinygltf types into native OPENGL types, implement an adapter");
  GL_TODO("Support multiple meshes and multiple primitives");
  GL_TODO("Support textures");
  GL_TODO("Support lighting");
  GL_TODO("Add model transformations");

  m_Model.LoadGLTFBinaryModel("../assets/models/Box.glb");
}

void GLTFViewerLayer::OnUpdate(GLCore::Timestep dt)
{
  // rotate camera
  if (m_RotateCamera) {
    m_TotalTime += dt.GetSeconds();
    auto* camera = GLCore::Application::Instance().GetMainCamera();
    auto position = camera->GetPosition();
    position.x = sin(m_TotalTime) * 3.0f;
    position.z = cos(m_TotalTime) * 3.0f;
    camera->SetPosition(position);
  }

  if (m_WireFrame) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  m_Model.GetShader().SetUniform("vProjectionMatrix", GLCore::Application::Instance().GetMainCamera()->GetProjection());
  m_Model.Draw();

  if (m_WireFrame) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GLTFViewerLayer::OnImGuiUpdate(GLCore::Timestep dt)
{
  ImGui::Begin(GetName());

  if (ImGui::Button("Load box")) {
    m_Model.LoadGLTFBinaryModel("../assets/models/Box.glb");
  }
  if (ImGui::Button("Load avocado")) {
    m_Model.LoadGLTFBinaryModel("../assets/models/Avocado.glb");
  }
  ImGui::Separator();

  if (m_Model.IsLoaded()) {
    ImGui::Text("Model transform:");
    auto position = m_Model.GetPosition();
    if (ImGui::SmallButton("Reset position")) {
      position = {0, 0, 0};
    }
    ImGui::DragFloat3("Position", &position[0], 0.05f);

    auto scale = m_Model.GetScale();

    if (ImGui::SmallButton("Reset scale")) {
      scale = {1, 1, 1};
    }
    ImGui::DragFloat3("Scale", &scale[0], 0.05f);

    auto rotation = m_Model.GetRotation();

    if (ImGui::SmallButton("Reset rotation")) {
      rotation = {0, 0, 0};
    }
    ImGui::DragFloat3("Rotation", &rotation[0], 0.5f);

    m_Model.SetPosition(position);
    m_Model.SetScale(scale);
    m_Model.SetRotation(rotation);
  }

  ImGui::Separator();
  ImGui::Text("Settings:");
  ImGui::Checkbox("Wireframe", &m_WireFrame);
  ImGui::Checkbox("Rotate camera", &m_RotateCamera);
  ImGui::End();
}

}  // namespace GLSandbox
