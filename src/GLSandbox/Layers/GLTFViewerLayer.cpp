#include <GLSandbox/Layers/GLTFViewerLayer.h>
#include <GLCore/Core/GLFWGlad.h>

#include <iostream>

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

  for (auto& primitive : mesh.primitives) {
    auto accessor = m_model.accessors[primitive.attributes["POSITION"]];
    auto bufferView = m_model.bufferViews[accessor.bufferView];

    auto buffer = m_model.buffers[bufferView.buffer];

    const float* positions = reinterpret_cast<const float*>(&buffer.data[bufferView.byteOffset + bufferView.byteLength]);

    // LOG_INFO("Loaded GLTF model, vertices:");
    for (size_t i = 0; i < accessor.count; ++i) {
      // LOG_INFO("[{0},{1},{2}]", positions[i * 3 + 0], positions[i * 3 + 1], positions[i * 3 + 2]);
    }
    // LOG_INFO("GLTF vertices end;");
  }

  // Rendering buffers
  m_basicShader.LoadShadersFromFiles("../assets/shaders/shader.vert.glsl", "../assets/shaders/shader.frag.glsl");
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  //
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void GLTFViewerLayer::OnDetach()
{
}

void GLTFViewerLayer::OnUpdate(GLCore::Timestep dt)
{
  if (!m_modelLoaded) return;
}

}  // namespace GLSandbox
