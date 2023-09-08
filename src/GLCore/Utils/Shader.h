#pragma once
#include <string>

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

  void LoadShadersFromFiles(std::string vertexPath, std::string fragmentPath);

 private:
  unsigned int m_programID;
};
}  // namespace GLCore
