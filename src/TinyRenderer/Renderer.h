#pragma once
#include <memory>
#include <glm/vec2.hpp>

namespace GLCore
{
class TextureBuffer;
struct Color;
}  // namespace GLCore

namespace tinyrenderer
{
class Renderer
{
 public:
  void BindTextureBuffer(std::weak_ptr<GLCore::TextureBuffer> buffer);

  void Line2D(glm::vec2 start, glm::vec2 end, GLCore::Color color);

 private:
  float DiagonalDistance(glm::vec2 p1, glm::vec2 p2);

  std::weak_ptr<GLCore::TextureBuffer> m_BoundBuffer;
};
}  // namespace tinyrenderer
