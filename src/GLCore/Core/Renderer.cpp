#include <GLCore/Core/Renderer.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace GLCore {

// =============================================================
// LINES
// =============================================================
void LinesRenderer::Create()
{
  // m_basicShader.LoadShadersFromFiles("../assets/shaders/shader.vert.glsl", "../assets/shaders/shader.frag.glsl");

  m_vertexCount = 0;
  m_vertexAttribIndex = 0;
  m_colorAttribIndex = 1;

  // Generate buffers
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(2, m_VBOs);

  glBindVertexArray(m_VAO);
  glEnableVertexAttribArray(m_vertexAttribIndex);
  glEnableVertexAttribArray(m_colorAttribIndex);

  // Vertex buffers
  //
  // vertices
  glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[0]);
  glVertexAttribPointer(m_vertexAttribIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_DYNAMIC_DRAW);
  // colors
  glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[1]);
  glVertexAttribPointer(m_colorAttribIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glBufferData(GL_ARRAY_BUFFER, sizeof(m_colors), m_colors, GL_DYNAMIC_DRAW);

  // TODO check errors?
}

void LinesRenderer::Destroy()
{
  if (m_VAO) {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(2, m_VBOs);
    m_VAO = 0;
  }
}

void LinesRenderer::Flush()
{
  if (m_vertexCount == 0) return;

  m_basicShader.Use();
  glBindVertexArray(m_VAO);

  glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[0]);
  glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertexCount * sizeof(glm::vec2), m_vertices);

  glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[1]);
  glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertexCount * sizeof(glm::vec4), m_colors);

  glDrawArrays(GL_LINES, 0, m_vertexCount);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glUseProgram(0);

  m_vertexCount = 0;
}

void LinesRenderer::Vertex(glm::vec2 p, glm::vec4 color)
{
  if (m_vertexCount == MAX_VERTICES) Flush();

  m_vertices[m_vertexCount] = p;
  m_colors[m_vertexCount] = color;
  m_vertexCount++;
}

// =============================================================
// Renderer
// =============================================================
void Renderer2D::Create()
{
  m_lines.Create();
}

void Renderer2D::Destroy()
{
  m_lines.Destroy();
}

void Renderer2D::Flush()
{
  m_lines.Flush();
}

void Renderer2D::DrawLine(glm::vec2 a, glm::vec2 b, glm::vec4 color)
{
  m_lines.Vertex(a, color);
  m_lines.Vertex(b, color);
}

}  // namespace GLCore
