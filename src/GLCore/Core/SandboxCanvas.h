#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/vec2.hpp>

namespace GLCore {
class SandboxCanvas {
 public:
  void Create();
  void Destroy();

  void ResizeCanvas(glm::vec2 size);

  void Bind();
  void Unbind();

  glm::vec2 GetSize();
  GLuint GetTextureID();

 private:
  glm::vec2 m_size;

  GLuint m_FBO;
  GLuint m_texture;
  GLuint m_RBO;
};
}  // namespace GLCore
