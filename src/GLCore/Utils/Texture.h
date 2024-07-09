#pragma once
#include <GLCore/Utils/Log.h>
#include <GLCore/Core/GLFWGlad.h>
#include <glm/vec2.hpp>

#include <array>

namespace GLCore
{
struct Color
{
  union
  {
    struct
    {
      unsigned char r, g, b, a;
    };
    unsigned char raw[4];
    unsigned int val;
  };

  Color() : Color(0, 0, 0, 1){};
  Color(unsigned char R, unsigned char G, unsigned char B, unsigned char A) : r(R), g(G), b(B), a(A)
  {
  }
};

// ====================================================
struct ColorLibrary
{
  inline static Color White{255, 255, 255, 255};
  inline static Color Red{255, 0, 0, 255};
  inline static Color Green{0, 255, 0, 255};
  inline static Color Blue{0, 0, 255, 255};
  inline static Color Black{0, 0, 0, 255};
};

// ====================================================
class TextureBuffer
{
 public:
  using T_DataType = Color;
  TextureBuffer(GLuint width, GLuint height);
  ~TextureBuffer();

  GLuint GetWidth();
  GLuint GetHeight();
  const T_DataType* GetBuffer();

  void SetPixel(size_t x, size_t y, Color col);
  void SetPixel(glm::vec2 p, Color col);

 private:
  const GLuint m_Width;
  const GLuint m_Height;

  T_DataType* m_Data;
};

// ====================================================
GL_TODO("Maybe texture should hold the buffer instead of providing it like this? Or a weak_ptr");
class Texture
{
 public:
  Texture();
  ~Texture();

  void SetImageData(GLuint width, GLuint height, const void* pixels);
  void SetImageData(TextureBuffer& buffer);

  void Bind();
  void Unbind();

  unsigned int GetTextureID();

 private:
  GLuint m_width;
  GLuint m_height;

  unsigned int m_textureID;
};

}  // namespace GLCore
