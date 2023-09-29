#pragma once
#include <GLCore/Utils/Shader.h>
#include <GLCore/Utils/Texture.h>
#include <GLCore/Core/GLFWGlad.h>

#include <GLM/vec2.hpp>
#include <GLM/vec4.hpp>

namespace GLCore {

class LinesRenderer {
 public:
  void Create();
  void Destroy();

  void Flush();

  void Vertex(glm::vec2 p, glm::vec4 color);

 private:
  GLuint m_VAO;
  GLuint m_VBOs[2];
  GLint m_vertexAttribIndex;
  GLint m_colorAttribIndex;

  static constexpr size_t MAX_VERTICES = 1024;
  glm::vec2 m_vertices[1024];
  glm::vec4 m_colors[1024];
  int m_vertexCount;

  Shader m_basicShader;
};

// TODO:
//  - Generalize to a triangle renderer?
//  - The vertices positions shouldn't be absolute, use model/world transform the position/size to correct world coordinates
class QuadRenderer {
 public:
  void Create();
  void Destroy();

  void Flush();

  void Quad(glm::vec2 center, glm::vec2 size, Texture* texture);

 private:
  GLuint m_VAO;
  GLuint m_VBO;

  static constexpr size_t MAX_QUADS = 10;
  static constexpr size_t FLOATS_PER_QUAD = 24;
  float m_vertices[MAX_QUADS * FLOATS_PER_QUAD];  // 2 vertices, 2 UV per Quad, Z is always 0.0f
  Texture* m_textures[MAX_QUADS];

  int m_vertexCount;

  Shader m_texShader;
};

class Renderer2D {
 public:
  static Renderer2D* Get();
  void Create();
  void Destroy();

  // Outputs all the collected vertices/lines and resets buffers
  // Should happen when buffer is full or end of the frame
  void Flush();

  // Drawing interface
  void DrawLine(glm::vec2 a, glm::vec2 b, glm::vec4 color);
  void DrawCircle(glm::vec2 center, float radius, glm::vec4 color);
  void DrawQuad(glm::vec2 center, glm::vec2 size, Texture* texture);
  void DrawTriangle(){};  // todo

 private:
  LinesRenderer m_lines;
  QuadRenderer m_quads;
};
}  // namespace GLCore
