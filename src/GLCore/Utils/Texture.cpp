#include <GLCore/Utils/Texture.h>

namespace GLCore
{

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

void Texture::SetImageData(GLuint width, GLuint height, const void* pixels)
{
  m_width = width;
  m_height = height;
  glBindTexture(GL_TEXTURE_2D, m_textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetImageData(TextureBuffer& buffer)
{
  SetImageData(buffer.GetWidth(), buffer.GetWidth(), buffer.GetBuffer());
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

// ==================================================================

TextureBuffer::TextureBuffer(GLuint width, GLuint height) : m_Width(width), m_Height(height)
{
  m_Data = new T_DataType[m_Width * m_Height];
}

TextureBuffer::~TextureBuffer()
{
  delete[] m_Data;
}
const TextureBuffer::T_DataType* TextureBuffer::GetBuffer()
{
  return m_Data;
}

GLuint TextureBuffer::GetWidth()
{
  return m_Width;
}

GLuint TextureBuffer::GetHeight()
{
  return m_Height;
}

void TextureBuffer::SetPixel(size_t x, size_t y, Color col)
{
  m_Data[y * m_Width + x] = col;
}

void TextureBuffer::SetPixel(glm::vec2 p, Color col)
{
  SetPixel(p.x, p.y, col);
}

}  // namespace GLCore
