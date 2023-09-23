#include <GLCore/Core/Renderer.h>
#include <GLCore/Core/Application.h>

namespace GLCore {

// =============================================================
// LINES
// =============================================================
void LinesRenderer::Create()
{
  m_basicShader.LoadShadersFromFiles("../assets/shaders/shader.vert.glsl", "../assets/shaders/shader.frag.glsl");

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

  m_basicShader.SetUniform("vProjectionMatrix", Application::Instance().GetMainCamera()->GetProjectionMatrix());

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

size_t LinesRenderer::Count()
{
  // This is going to be 0 when ImGui layer tries to get it. It's because we Flush() at the end of framebuffer frame.
  // Flush() resets number of vertices for this frame, so it's going to be 0 til next frame.
  // TODO: Count vertices separately during stat counting for this frame
  // TODO: Add more stats like: render time
  return m_vertexCount;
}

Renderer2D* Renderer2D::Get()
{
  return Application::Instance().GetRenderer();
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

size_t Renderer2D::GetLinesCount()
{
  return m_lines.Count();
}

}  // namespace GLCore
