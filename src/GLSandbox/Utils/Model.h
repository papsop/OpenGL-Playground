#pragma once
#include <GLSandbox/gltf/tiny_gltf.h>
#include <GLCore/Utils/Shader.h>

#include <glm/glm.hpp>

#include <string>
#include <array>

namespace GLSandbox {
class Model {
 public:
  Model();
  Model(std::string modelPath);
  Model(const Model&) = delete;
  Model& operator=(const Model&) = delete;

  ~Model();

  bool LoadGLTFBinaryModel(std::string path);
  bool IsLoaded();

  void SetPosition(glm::vec3 position);
  void SetRotation(glm::vec3 rotation);
  void SetScale(glm::vec3 scale);

  glm::vec3 GetPosition();
  glm::vec3 GetScale();
  glm::vec3 GetRotation();

  GLCore::Shader& GetShader();
  void Draw();

  glm::mat4 GetModelTransformMatrix();

 private:
  void BindBuffers();
  void UnbindBuffers();

  tinygltf::Model m_Model;
  GLCore::Shader m_Shader;
  bool m_IsModelLoaded;

  // model transformations
  bool m_IsTransformDirty;
  glm::mat4 m_Transform = glm::mat4(1.0f);
  glm::vec3 m_Position = {0, 0, 0};
  glm::vec3 m_Rotation = {0, 0, 0};
  glm::vec3 m_Scale = {1, 1, 1};

  // buffers for opengl
  // number of buffers depends on the model data (meshes, primitives)
  unsigned int m_VBO = 0;
  unsigned int m_VAO = 0;
  unsigned int m_EBO = 0;
};
}  // namespace GLSandbox
