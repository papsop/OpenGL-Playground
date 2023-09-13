#pragma once

namespace GLCore {
class Renderer2D {
 public:
  void Create();
  void Destroy();

  // Outputs all the collected vertices/lines and resets buffers
  // Should happen when buffer is full or end of the frame
  void Flush();

  void DrawLine();
  void DrawCircle();
  void DrawTriangle();
};
}  // namespace GLCore
