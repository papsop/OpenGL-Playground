#include <TinyRenderer/Renderer.h>
#include <GLCore/Utils/Texture.h>

#include <glm/gtx/compatibility.hpp>

namespace tinyrenderer
{
void Renderer::BindTextureBuffer(std::weak_ptr<GLCore::TextureBuffer> buffer)
{
  m_BoundBuffer = buffer;
}

// ===================================================================
float Renderer::DiagonalDistance(glm::vec2 p1, glm::vec2 p2)
{
  return std::max(std::abs(p1.x - p2.x), std::abs(p1.y - p2.y));
}

// ===================================================================
void Renderer::Line2D(glm::vec2 start, glm::vec2 end, GLCore::Color col)
{
  if (auto buffer = m_BoundBuffer.lock())
  {
    float maxSteps = DiagonalDistance(start, end);
    for (size_t step = 0; step <= maxSteps; step++)
    {
      float t = (maxSteps == 0) ? 0.0f : step / maxSteps;
      buffer->SetPixel(glm::round(glm::lerp(start, end, t)), col);
    }
  }
}

}  // namespace tinyrenderer
