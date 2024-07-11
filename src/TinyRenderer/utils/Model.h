#pragma once

#include <glm/vec3.hpp>
#include <string>
#include <vector>

namespace tinyrenderer
{
class Model
{
 public:
  Model() = default;
  Model(std::string filePath);
  Model(const Model&) = delete;
  Model& operator=(const Model&) = delete;

  size_t VertsSize();
  size_t FacesSize();

  bool IsLoaded();

  glm::vec3 Vertex(size_t i);
  std::vector<int>& Face(size_t i);

  bool LoadOBJModel(std::string filePath);

 private:
  std::vector<glm::vec3> m_Verts;
  std::vector<std::vector<int>> m_Faces;
};
}  // namespace tinyrenderer
