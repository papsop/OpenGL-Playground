#pragma once
#include <GLCore/Core/GLFWGlad.h>
#include <glm/vec2.hpp>

namespace GLCore {
class SandboxCanvas {
 public:
  void Create();
  void Destroy();

  void ResizeCanvas(GLsizei width, GLsizei height);

  void Bind();
  void Unbind();

  GLsizei GetWidth();
  GLsizei GetHeight();
  uint64_t GetTextureID();

 private:
  GLsizei m_width;
  GLsizei m_height;

  GLuint m_FBO;
  GLuint m_texture;
  GLuint m_RBO;
};
}  // namespace GLCore
