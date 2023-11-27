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
};
}  // namespace flux
