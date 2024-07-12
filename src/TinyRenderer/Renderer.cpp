#include <TinyRenderer/Renderer.h>
#include <TinyRenderer/utils/Model.h>

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
// https://github.com/ssloy/tinyrenderer/wiki/Lesson-1:-Bresenham%E2%80%99s-Line-Drawing-Algorithm
// https://www.redblobgames.com/grids/line-drawing/
void Renderer::DrawLine2D(glm::vec2 start, glm::vec2 end, GLCore::Color color)
{
  if (auto buffer = m_BoundBuffer.lock())
  {
    float maxSteps = DiagonalDistance(start, end);
    for (size_t step = 0; step <= maxSteps; step++)
    {
      float t = (maxSteps == 0) ? 0.0f : step / maxSteps;
      buffer->SetPixel(glm::round(glm::lerp(start, end, t)), color);
    }
  }
}

// ===================================================================
// https://github.com/ssloy/tinyrenderer/wiki/Lesson-1:-Bresenham%E2%80%99s-Line-Drawing-Algorithm
void Renderer::DrawModelWireframe(glm::vec2 size, const Model& model)
{
  if (!model.IsLoaded()) return;

  for (size_t i = 0; i < model.FacesSize(); i++)
  {
    std::vector<int> face = model.Face(i);
    for (size_t j = 0; j < 3; j++)
    {
      // Get 3d points for given triangle face
      glm::vec3 v0 = model.Vertex(face[j]);
      glm::vec3 v1 = model.Vertex(face[(j + 1) % 3]);

      // Remap these points to 2d texture coords
      float width = size.x;
      float height = size.y;
      glm::vec2 p0 = {(v0.x + 1.) * width / 2., (v0.y + 1) * height / 2.};
      glm::vec2 p1 = {(v1.x + 1.) * width / 2., (v1.y + 1) * height / 2.};

      // draw line
      DrawLine2D(p0, p1, GLCore::ColorLibrary::White);
    }
  }
}

// ===================================================================
// https://github.com/ssloy/tinyrenderer/wiki/Lesson-2:-Triangle-rasterization-and-back-face-culling
void Renderer::DrawTriangle(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2, GLCore::Color col)
{
  if (p0.y == p1.y && p0.y == p1.y) return;

  if (auto buffer = m_BoundBuffer.lock())
  {
    // Sort vertices in y-direction asc
    if (p0.y > p1.y) std::swap(p0, p1);
    if (p0.y > p2.y) std::swap(p0, p2);
    if (p1.y > p2.y) std::swap(p1, p2);

    int totalHeight = p2.y - p0.y;
    int lowerSegmentHeight = p1.y - p0.y + 1;
    int upperSegmentHeight = totalHeight - lowerSegmentHeight + 1;
    for (int y = p0.y; y <= p2.y; y++)
    {
      // Basically doing a lerp on triangle faces
      //
      //  p2                            -            -
      //  |  \                          |            |
      //  |    \               UpperSegmentHeight    |
      //  |      \                      |            |
      //  |       \                     |        TotalHeight
      //  |        p1         _         -            |
      //  |       /           |                      |
      // pA<-y->pB   LowerSegmentHeight              |
      //  |    /              |                      |
      //  |  /                |                      |
      //  p0                  -                      -
      //
      float totalT = (y - p0.y) / totalHeight;
      glm::vec2 pA = p0 + (p2 - p0) * totalT;

      if (y > p1.y)
      {  // upper segment
        float segmentT = (upperSegmentHeight > 0) ? (y - p1.y) / upperSegmentHeight : 0.0f;

        glm::vec2 pB = p1 + (p2 - p1) * segmentT;

        if (pA.x > pB.x) std::swap(pA, pB);
        for (int x = pA.x; x <= pB.x; x++)
        {
          buffer->SetPixel(x, y, col);
        }
      }
      else
      {  // lower segment
        float segmentT = (lowerSegmentHeight > 0) ? (y - p0.y) / lowerSegmentHeight : 0.0f;

        glm::vec2 pB = p0 + (p1 - p0) * segmentT;

        if (pA.x > pB.x) std::swap(pA, pB);
        for (int x = pA.x; x <= pB.x; x++)
        {
          buffer->SetPixel(x, y, col);
        }
      }
    }

    // Outline
    DrawLine2D(p0, p1, col);
    DrawLine2D(p1, p2, col);
    DrawLine2D(p2, p0, col);
  }
}

}  // namespace tinyrenderer
