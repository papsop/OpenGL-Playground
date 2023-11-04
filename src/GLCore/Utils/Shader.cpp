#include <GLCore/Utils/Shader.h>
#include <GLCore/Utils/Log.h>

#include <glad/glad.h>
#include <fstream>
#include <sstream>

namespace GLCore {
unsigned int Shader::GetProgramID()
{
  return m_programID;
}

void Shader::Use()
{
  glUseProgram(m_programID);
}

void Shader::LoadShadersFromFiles(std::string vertexPath, std::string fragmentPath)
{
  std::string vShaderCode;
  std::string fShaderCode;

  try {
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);

    std::stringstream vShaderStream;
    std::stringstream fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    vShaderCode = vShaderStream.str();
    fShaderCode = fShaderStream.str();
  }
  catch (std::exception e) {
    LOG_FATAL("Unable to open shader files, error: {0}", e.what());
  }

  const char* vertexShaderCode = vShaderCode.c_str();
  const char* fragmentShaderCode = fShaderCode.c_str();

  unsigned int vertexProgramID;
  unsigned int fragmentProgramID;

  int success;
  char info[512];
  // VERTEX shader
  vertexProgramID = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexProgramID, 1, &vertexShaderCode, NULL);
  glCompileShader(vertexProgramID);
  glGetShaderiv(vertexProgramID, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexProgramID, 512, NULL, info);
    LOG_FATAL("Error while compiling vertex shader: {0}", info);
  }
  LOG_INFO("Vertex shader '{0}' compiled", vertexPath);

  // FRAGMENT shader
  fragmentProgramID = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentProgramID, 1, &fragmentShaderCode, NULL);
  glCompileShader(fragmentProgramID);
  if (!success) {
    glGetShaderInfoLog(fragmentProgramID, 512, NULL, info);
    LOG_FATAL("Error while compiling vertex shader: {0}", info);
  }
  LOG_INFO("Fragment shader '{0}' compiled", fragmentPath);

  // COMBINE
  m_programID = glCreateProgram();
  glAttachShader(m_programID, vertexProgramID);
  glAttachShader(m_programID, fragmentProgramID);
  glLinkProgram(m_programID);

  glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(m_programID, 512, NULL, info);
    LOG_FATAL("Error while linking shaders: {0}", info);
  }

  glDeleteShader(vertexProgramID);
  glDeleteShader(fragmentProgramID);
}

void Shader::SetUniform(std::string name, int value)
{
  glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
}

void Shader::SetUniform(std::string name, bool value)
{
  glUniform1i(glGetUniformLocation(m_programID, name.c_str()), (int)value);
}

void Shader::SetUniform(std::string name, float value)
{
  glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
}

void Shader::SetUniform(std::string name, glm::mat4 value)
{
  glUniformMatrix4fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniform(std::string name, glm::vec4 value)
{
  glUniform4f(glGetUniformLocation(m_programID, name.c_str()), value.r, value.g, value.b, value.a);
}

}  // namespace GLCore
