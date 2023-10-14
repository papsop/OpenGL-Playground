#include <GLCore/Core/Renderer.h>
#include <GLCore/Core/Application.h>

#include <glm/ext/scalar_constants.hpp>

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

  m_basicShader.SetUniform("vProjectionMatrix", Application::Instance().GetMainCamera()->GetProjection());

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
// QUADS
// =============================================================

void QuadRenderer::Create()
{
  m_texShader.LoadShadersFromFiles("../assets/shaders/texShader.vert.glsl", "../assets/shaders/texShader.frag.glsl");

  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void QuadRenderer::Destroy()
{
  if (m_VAO) {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    m_VAO = 0;
  }
}

void QuadRenderer::Flush()
{
  if (m_vertexCount == 0) return;

  m_texShader.Use();
  m_texShader.SetUniform("vProjectionMatrix", GLCore::Application::Instance().GetMainCamera()->GetProjection());

  // Fill buffer for this flush
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Use Vertex array to draw all the buffered vertices
  glBindVertexArray(m_VAO);
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  for (size_t i = 0; i < m_vertexCount; i++) {
    auto* quadTexture = m_textures[i];
    if (quadTexture) quadTexture->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);  // 6 vertices (*4 floats, 2D position + UV) per vertex
    if (quadTexture) quadTexture->Unbind();
  }

  glBindVertexArray(0);
  m_vertexCount = 0;
}

void QuadRenderer::Quad(glm::vec2 center, glm::vec2 size, Texture* texture)
{
  if (m_vertexCount == MAX_QUADS) Flush();

  m_textures[m_vertexCount] = texture;
  float half_width = size.x / 2;
  float half_height = size.y / 2;
  // clang-format off
  GL_TODO("Should't use absolute vertex positions, use model/world transforms to apply the offset")
  float quadVertices[] = {
    // positions   // texCoords
    -half_width + center.x, half_height + center.y,  0.0f, 1.0f,
    -half_width + center.x, -half_height + center.y,  0.0f, 0.0f,
     half_width + center.x, -half_height + center.y,  1.0f, 0.0f,

    -half_width + center.x,  half_height + center.y,  0.0f, 1.0f,
     half_width + center.x, -half_height + center.y,  1.0f, 0.0f,
     half_width + center.x,  half_height + center.y,  1.0f, 1.0f
  };
  // clang-format on
  memcpy(&m_vertices[m_vertexCount], quadVertices, sizeof(quadVertices));
  m_vertexCount++;
}
// =============================================================
// Renderer
// =============================================================

Renderer2D* Renderer2D::Get()
{
  return Application::Instance().GetRenderer();
}

void Renderer2D::Create()
{
  m_lines.Create();
  m_quads.Create();
}

void Renderer2D::Destroy()
{
  m_lines.Destroy();
  m_quads.Destroy();
}

void Renderer2D::Flush()
{
  m_lines.Flush();
  m_quads.Flush();
}

void Renderer2D::DrawLine(glm::vec2 a, glm::vec2 b, glm::vec4 color)
{
  m_lines.Vertex(a, color);
  m_lines.Vertex(b, color);
}

void Renderer2D::DrawCircle(glm::vec2 center, float radius, glm::vec4 color)
{
  // for an actual nice circle, canvas has to be square, otherwise it get stretched
  float increments = 20.0f;
  float relativeIncrement = glm::pi<float>() * 2.0f / increments;
  float sinInc = sin(relativeIncrement);
  float cosInc = cos(relativeIncrement);
  glm::vec2 p1{1.0f, 0.0f};
  glm::vec2 w1 = center + radius * p1;
  for (size_t i = 0; i < increments; i++) {
    // https://math.stackexchange.com/a/814981
    glm::vec2 p2;
    p2.x = cosInc * p1.x - sinInc * p1.y;
    p2.y = sinInc * p1.x + cosInc * p1.y;
    glm::vec2 w2;
    w2 = center + radius * p2;
    m_lines.Vertex(w1, color);
    m_lines.Vertex(w2, color);
    w1 = w2;
    p1 = p2;
  }
}

void Renderer2D::DrawQuad(glm::vec2 center, glm::vec2 size, Texture* texture)
{
  m_quads.Quad(center, size, texture);
}

}  // namespace GLCore
