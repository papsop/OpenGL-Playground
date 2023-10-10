#pragma once
#include <GLCore/Core/GLFWGlad.h>

namespace GLCore {
class Texture {
 public:
  Texture();
  ~Texture();

  void SetImageData(GLuint width, GLuint height, const void* pixels);
  void Bind();
  void Unbind();

  unsigned int GetTextureID();

 private:
  GLuint m_width;
  GLuint m_height;

  unsigned int m_textureID;
};
}  // namespace GLCore
