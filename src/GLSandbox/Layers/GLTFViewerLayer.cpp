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
  auto positionAccessor = m_model.accessors[primitive.attributes["POSITION"]];
  auto indexAccessor = m_model.accessors[primitive.indices];
  auto positionBufferView = m_model.bufferViews[positionAccessor.bufferView];
  auto indexBufferView = m_model.bufferViews[indexAccessor.bufferView];
  auto positionBuffer = m_model.buffers[positionBufferView.buffer];
  auto indexBuffer = m_model.buffers[indexBufferView.buffer];

  // Rendering buffers
  m_basicShader.LoadShadersFromFiles("../assets/shaders/basic.vert.glsl", "../assets/shaders/basic.frag.glsl");
  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  // positions
  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, positionBufferView.byteLength, &positionBuffer.data.at(0) + positionBufferView.byteOffset + positionAccessor.byteOffset, GL_STATIC_DRAW);

  // indices
  glGenBuffers(1, &m_EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferView.byteLength, &indexBuffer.data.at(0) + indexBufferView.byteOffset + indexAccessor.byteOffset, GL_STATIC_DRAW);

  // location 0 - vertex pos
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void GLTFViewerLayer::OnDetach()
{
  if (m_VAO) {
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    glDeleteVertexArrays(1, &m_VAO);
    m_VAO = 0;
  }
}

void GLTFViewerLayer::OnUpdate(GLCore::Timestep dt)
{
  // if (!m_modelLoaded) return;
  auto& mesh = m_model.meshes[0];
  auto primitive = mesh.primitives[0];
  auto positionAccessor = m_model.accessors[primitive.attributes["POSITION"]];
  auto indexAccessor = m_model.accessors[primitive.indices];

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
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  // Draw the triangle !
  m_basicShader.Use();
  m_basicShader.SetUniform("vProjectionMatrix", GLCore::Application::Instance().GetMainCamera()->GetProjection());
  //glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(accessor.count));  // Starting from vertex 0; 3 vertices total -> 1 triangle
  glDrawElements(GL_TRIANGLES, indexAccessor.count, indexAccessor.componentType, (void*)0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  if (m_wireFrame) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GLTFViewerLayer::OnImGuiUpdate(GLCore::Timestep dt)
{
  ImGui::Begin(GetName());

  if (m_modelLoaded)
  {
    GL_TODO("Don't access mesh[0] directly");
    auto& mesh = m_model.meshes[0];
    ImGui::Text("Model information:");
    ImGui::Text("Meshes: %d", m_model.meshes.size());
    ImGui::Text("Primitives: %d", mesh.primitives.size());
    ImGui::Text("Render mode: %d", mesh.primitives[0].mode);
  }

  ImGui::Separator();
  ImGui::Text("Settings:");
  ImGui::Checkbox("Wireframe", &m_wireFrame);
  ImGui::Checkbox("Rotate camera", &m_rotateCamera);
  ImGui::End();
}

}  // namespace GLSandbox
