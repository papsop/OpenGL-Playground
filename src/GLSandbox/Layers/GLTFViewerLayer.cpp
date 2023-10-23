#include <GLSandbox/Layers/GLTFViewerLayer.h>
#include <GLCore/Core/Application.h>
#include <GLCore/Core/GLFWGlad.h>

#include <iostream>
#include <imgui.h>

namespace GLSandbox {

void GLTFViewerLayer::OnAttach()
{
  // GLTF Loading
  std::string err;
  std::string warn;

  m_modelLoaded = m_loader.LoadBinaryFromFile(&m_model, &err, &warn, "../assets/models/Box.glb");

  if (!err.empty()) LOG_ERROR(err);
  if (!warn.empty()) LOG_WARN(warn);

  if (!m_modelLoaded) {
    return;
  }

  auto& mesh = m_model.meshes[0];

  LOG_INFO("Loaded model:");
  LOG_INFO("\tMeshes: {0}", m_model.meshes.size());
  LOG_INFO("\tPrimitives: {0}", mesh.primitives.size());

  auto primitive = mesh.primitives[0];
  auto accessor = m_model.accessors[primitive.attributes["POSITION"]];
  auto bufferView = m_model.bufferViews[accessor.bufferView];
  auto buffer = m_model.buffers[bufferView.buffer];

  // Rendering buffers
  m_basicShader.LoadShadersFromFiles("../assets/shaders/basic.vert.glsl", "../assets/shaders/basic.frag.glsl");
  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);
  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

  glBufferData(GL_ARRAY_BUFFER, bufferView.byteLength, &buffer.data.at(0) + bufferView.byteOffset + accessor.byteOffset, GL_STATIC_DRAW);

  // glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertex_buffer_data), &m_vertex_buffer_data, GL_STATIC_DRAW);

  // location 0 - vertex pos
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void GLTFViewerLayer::OnDetach()
{
  if (m_VAO) {
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
    m_VAO = 0;
  }
}

void GLTFViewerLayer::OnUpdate(GLCore::Timestep dt)
{
  // if (!m_modelLoaded) return;
  auto& mesh = m_model.meshes[0];
  auto primitive = mesh.primitives[0];
  auto accessor = m_model.accessors[primitive.attributes["POSITION"]];
  auto bufferView = m_model.bufferViews[accessor.bufferView];
  auto buffer = m_model.buffers[bufferView.buffer];

  // rotate camera
  if (m_rotateCamera) {
    m_totalTime += dt.GetSeconds();
    auto* camera = GLCore::Application::Instance().GetMainCamera();
    auto position = camera->GetPosition();
    position.x = sin(m_totalTime) * 3.0f;
    position.z = cos(m_totalTime) * 3.0f;
    camera->SetPosition(position);
  }

  if (m_wireFrame) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glBindVertexArray(m_VAO);
  // Draw the triangle !
  m_basicShader.Use();
  m_basicShader.SetUniform("vProjectionMatrix", GLCore::Application::Instance().GetMainCamera()->GetProjection());
  glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(accessor.count));  // Starting from vertex 0; 3 vertices total -> 1 triangle
  glBindVertexArray(0);

  if (m_wireFrame) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GLTFViewerLayer::OnImGuiUpdate(GLCore::Timestep dt)
{
  ImGui::Begin(GetName());
  ImGui::Text("Settings:");
  ImGui::Checkbox("Wireframe", &m_wireFrame);
  ImGui::Checkbox("Rotate camera", &m_rotateCamera);
  ImGui::End();
}

}  // namespace GLSandbox
