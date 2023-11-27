#pragma once
#include <FluxPhysics/Utils/DebuggerAdapter.h>

namespace GLSandbox
{
class SandboxDebuggerAdapter final : public flux::I_DebuggerAdapter
{
 public:
  virtual void DrawLine(flux::Vec3f a, flux::Vec3f b, flux::Vec4f color) override;
  virtual void DrawCircle(flux::Vec3f center, float radius, flux::Vec4f color) override;
};
}  // namespace GLSandbox
