#include <GLCore/Utils/Texture.h>
#include <GLCore/Core/GLFWGlad.h>

namespace GLCore {

Texture::Texture() : m_width(0), m_height(0)
{
  glGenTextures(1, &m_textureID);
  glBindTexture(GL_TEXTURE_2D, m_textureID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // size increase/decrease
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  // WRAPPING
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
  glDeleteTextures(1, &m_textureID);
}

void Texture::SetImageData(float width, float height, const void* pixels)
{
  m_width = width;
  m_height = height;
  glBindTexture(GL_TEXTURE_2D, m_textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind()
{
  glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::Unbind()
{
  glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::GetTextureID()
{
  return m_textureID;
}

}  // namespace GLCore
