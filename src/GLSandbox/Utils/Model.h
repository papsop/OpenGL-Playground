#pragma once
#include <GLSandbox/gltf/tiny_gltf.h>
#include <glm/glm.hpp>

#include <string>
#include <array>

namespace GLSandbox {
class Model {
 public:
  Model();
  Model(const Model&) = delete;
  Model& operator=(const Model&) = delete;

  ~Model() = default;

  void SetPosition(glm::vec3 position);
  void SetRotation(glm::vec3 rotation);
  void SetScale(glm::vec3 scale);

  glm::vec3 GetPosition();
  glm::vec3 GetScale();

  void Draw();

  glm::mat4 GetModelTransformMatrix();

 private:
  tinygltf::Model m_Model;

  // model transformations
  bool m_IsTransformDirty;
  glm::mat4 m_Transform = glm::mat4(1.0f);
  glm::vec3 m_Position = {0, 0, 0};
  glm::vec3 m_Rotation = {0, 0, 0};
  glm::vec3 m_Scale = {1, 1, 1};

  // buffers for opengl
  // number of buffers depends on the model data (meshes, primitives)
  std::vector<unsigned int> m_VAO;
  std::vector<unsigned int> m_VBO;
  std::vector<unsigned int> m_EBO;
};
}  // namespace GLSandbox
