#pragma once
#include <string>

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GLCore {
class Shader {
 public:
  Shader() = default;
  ~Shader() = default;

  unsigned int GetProgramID();

  void Use();

  void SetUniform(std::string name, int value);
  void SetUniform(std::string name, float value);
  void SetUniform(std::string name, bool value);
  // add more when needed
  void SetUniform(std::string name, glm::mat4x4 value);

  void LoadShadersFromFiles(std::string vertexPath, std::string fragmentPath);

 private:
  unsigned int m_programID;
};
}  // namespace GLCore
