#pragma once
#include <FluxPhysics/Utils/Vec.h>

namespace flux
{

// The project using this library can create its own DebuggerAdapter and connect it to world
// World will call virtual functions and use project's API do draw debug objects
// Functions aren't pure-virtual, because adapter doesn't have to support all of them
class I_DebuggerAdapter
{
 public:
  virtual void DrawLine(Vec3f a, Vec3f b, Vec4f color){};
  virtual void DrawCircle(Vec3f center, float radius, Vec4f color){};

  // clang-format off
  // TODO: Turn this into bit flags instead of this shit
  void SetDrawBody(bool val) { m_DrawBody = val; }
  void SetDrawDirection(bool val) { m_DrawDirection = val; }

  bool ShouldDrawBody() { return m_DrawBody; } 
  bool ShouldDrawDirection() { return m_DrawDirection; }
  // clang-format on

 private:
  bool m_DrawBody = false;
  bool m_DrawDirection = false;
};
}  // namespace flux
