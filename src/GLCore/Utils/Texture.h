#pragma once

namespace GLCore {
class Texture {
 public:
  Texture();
  ~Texture();

  void SetImageData(float width, float height, const void* pixels);
  void Bind();
  void Unbind();

  unsigned int GetTextureID();

 private:
  float m_width;
  float m_height;

  unsigned int m_textureID;
};
}  // namespace GLCore
