#include <GLSandbox/Utils/Model.h>

#include <GLCore/Core/GLFWGlad.h>
#include <GLCore/Utils/Log.h>

#include <glm/ext/matrix_transform.hpp>

// Get rid of quaternion minmax C4003 warning
#pragma warning(disable : 4003)
#include <glm/gtx/quaternion.hpp>

namespace GLSandbox {
Model::Model()
{
  m_IsTransformDirty = true;
  m_IsModelLoaded = false;
  m_Shader.LoadShadersFromFiles("../assets/shaders/basic.vert.glsl", "../assets/shaders/basic.frag.glsl");
}

Model::Model(std::string modelPath)
{
  m_IsTransformDirty = true;
  m_IsModelLoaded = LoadGLTFBinaryModel(modelPath);
  m_Shader.LoadShadersFromFiles("../assets/shaders/basic.vert.glsl", "../assets/shaders/basic.frag.glsl");
}

Model::~Model()
{
  if (m_IsModelLoaded) {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    m_IsModelLoaded = false;
  }
}

bool Model::LoadGLTFBinaryModel(std::string modelPath)
{
  std::string err;
  std::string warn;
  tinygltf::TinyGLTF m_Loader;

  m_Model = tinygltf::Model();
  bool binLoaded = m_Loader.LoadBinaryFromFile(&m_Model, &err, &warn, modelPath);

  if (!err.empty()) LOG_ERROR(err);
  if (!warn.empty()) LOG_WARN(warn);
  if (!binLoaded) return false;

  m_IsModelLoaded = LoadModelImpl();
  return m_IsModelLoaded;
}

bool Model::LoadGLTFModel(std::string modelPath)
{
  GL_TODO("Doesn't work right now, some 'invalid magic.' error when loading a JSON");
  std::string err;
  std::string warn;
  tinygltf::TinyGLTF m_Loader;

  m_Model = tinygltf::Model();
  bool gltfLoaded = m_Loader.LoadASCIIFromFile(&m_Model, &err, &warn, modelPath);

  if (!err.empty()) LOG_ERROR(err);
  if (!warn.empty()) LOG_WARN(warn);
  if (!gltfLoaded) return false;

  m_IsModelLoaded = LoadModelImpl();
  return m_IsModelLoaded;
}

bool Model::LoadModelImpl()
{
  // OpenGL buffers
  GL_TODO("Support multiple meshes");
  GL_TODO("Support multiple primitives");  // Buffer and draw call per primitive?

  auto& mesh = m_Model.meshes[0];
  auto& primitive = mesh.primitives[0];

  auto& positionAccessor = m_Model.accessors[primitive.attributes["POSITION"]];
  auto& indexAccessor = m_Model.accessors[primitive.indices];
  auto& positionBufferView = m_Model.bufferViews[positionAccessor.bufferView];
  auto& indexBufferView = m_Model.bufferViews[indexAccessor.bufferView];
  auto& positionBuffer = m_Model.buffers[positionBufferView.buffer];
  auto& indexBuffer = m_Model.buffers[indexBufferView.buffer];

  // Vertex array object
  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  // Vertex buffer object
  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, positionBufferView.byteLength, &positionBuffer.data.at(0) + positionAccessor.byteOffset + positionBufferView.byteOffset,
               GL_STATIC_DRAW);

  // Element buffer object - for indices
  glGenBuffers(1, &m_EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferView.byteLength, &indexBuffer.data.at(0) + indexAccessor.byteOffset + indexBufferView.byteOffset,
               GL_STATIC_DRAW);

  // Location 0 - position
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, positionAccessor.componentType, GL_FALSE, static_cast<GLsizei>(positionBufferView.byteStride), (void*)0);

  UnbindBuffers();

  // Information log
  LOG_INFO("Model loaded:");
  LOG_INFO("\tMeshes: {0}", m_Model.meshes.size());
  LOG_INFO("\tPrimitives: {0}", mesh.primitives.size());

  return true;
}

bool Model::IsLoaded()
{
  return m_IsModelLoaded;
}

void Model::SetPosition(glm::vec3 position)
{
  if (position == m_Position) return;
  m_Position = position;
  m_IsTransformDirty = true;
}

void Model::SetRotation(glm::vec3 rotation)
{
  if (rotation == m_Rotation) return;
  m_Rotation = rotation;
  m_IsTransformDirty = true;
}

void Model::SetScale(glm::vec3 scale)
{
  if (scale == m_Scale) return;
  m_Scale = scale;
  m_IsTransformDirty = true;
}

glm::vec3 Model::GetPosition()
{
  return m_Position;
}

glm::vec3 Model::GetScale()
{
  return m_Scale;
}

glm::vec3 Model::GetRotation()
{
  return m_Rotation;
}

GLCore::Shader& Model::GetShader()
{
  return m_Shader;
}

void Model::Draw()
{
  if (!m_IsModelLoaded) {
    // LOG_WARN("Trying to draw an empty Model");
    return;
  }

  auto& mesh = m_Model.meshes[0];
  auto& primitive = mesh.primitives[0];
  auto& material = m_Model.materials[primitive.material];
  auto& bcf = material.pbrMetallicRoughness.baseColorFactor;
  glm::vec4 baseColorFactor = glm::vec4(bcf[0], bcf[1], bcf[2], bcf[3]);

  auto& positionAccessor = m_Model.accessors[primitive.attributes["POSITION"]];
  auto& indexAccessor = m_Model.accessors[primitive.indices];

  // An owner of this model sets projection uniform
  m_Shader.Use();
  m_Shader.SetUniform("vModelMatrix", GetModelTransformMatrix());
  m_Shader.SetUniform("vColor", baseColorFactor);

  BindBuffers();
  glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexAccessor.count), indexAccessor.componentType, (void*)0);
  UnbindBuffers();
}

glm::mat4 Model::GetModelTransformMatrix()
{
  if (m_IsTransformDirty) {
    glm::vec3 radRotation = glm::radians(m_Rotation);
    glm::mat4 rotation = glm::toMat4(glm::quat(radRotation));
    glm::mat4 scale = glm::scale(glm::mat4{1.0f}, m_Scale);
    glm::mat4 translate = glm::translate(glm::mat4{1.0f}, m_Position);

    m_Transform = translate * scale * rotation;
    m_IsTransformDirty = false;
  }

  return m_Transform;
}

void Model::BindBuffers()
{
  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}

void Model::UnbindBuffers()
{
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}  // namespace GLSandbox
