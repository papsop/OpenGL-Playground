#include <GLSandbox/Utils/SandboxDebuggerAdapter.h>
#include <GLCore/Core/Renderer.h>
#include <GLCore/Core/Application.h>

namespace GLSandbox
{
void SandboxDebuggerAdapter::DrawLine(flux::Vec3f a, flux::Vec3f b, flux::Vec4f color)
{
  GLCore::Renderer2D::Get()->DrawLine({a.x, a.y}, {b.x, b.y},
                                      {
                                          color.r,
                                          color.g,
                                          color.b,
                                          color.a,
                                      });
}

void SandboxDebuggerAdapter::DrawCircle(flux::Vec3f center, float radius, flux::Vec4f color)
{
  GLCore::Renderer2D::Get()->DrawCircle({center.x, center.y}, radius,
                                        {
                                            color.r,
                                            color.g,
                                            color.b,
                                            color.a,
                                        });
}

}  // namespace GLSandbox
