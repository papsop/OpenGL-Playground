#include <GLSandbox/Layers/TestLayer.h>
#include <GLCore/Core/Application.h>

namespace GLSandbox {
void GLSandbox::TestLayer::OnUpdate(GLCore::Timestep dt)
{
  GLCore::Renderer2D::Get()->DrawLine({1.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});
  GLCore::Renderer2D::Get()->DrawLine({-1.0f, -1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});
}
}  // namespace GLSandbox
