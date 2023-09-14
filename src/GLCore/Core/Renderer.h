#pragma once
#include <GLCore/Utils/Shader.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

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
  size_t m_vertexCount;

  Shader m_basicShader;
};

class Renderer2D {
 public:
  void Create();
  void Destroy();

  // Outputs all the collected vertices/lines and resets buffers
  // Should happen when buffer is full or end of the frame
  void Flush();

  // Drawing interface
  void DrawLine(glm::vec2 a, glm::vec2 b, glm::vec4 color);
  void DrawCircle(){};    // todo
  void DrawTriangle(){};  // todo
 private:
  LinesRenderer m_lines;
};
}  // namespace GLCore
