#include <GLSandbox/Layers/TestLayer.h>
#include <GLCore/Core/Application.h>

namespace GLSandbox {
void GLSandbox::TestLayer::OnUpdate(GLCore::Timestep dt)
{
  GLCore::Renderer2D::Get()->DrawLine({-5.0, -5.0f}, {5.0f, 5.0f}, {0.7f, 0.7f, 0.7f, 1.0f});
  GLCore::Renderer2D::Get()->DrawLine({-5.0, 5.0f}, {5.0f, -5.0f}, {0.7f, 0.7f, 0.7f, 1.0f});
}

void TestLayer::OnMouseInputEvent(const GLCore::MouseInputEvent& e)
{
  if (e.Type != GLCore::MouseInputEvent::LeftClickPressed) return;
  LOG_INFO("received leftclick mouse event");
}

void TestLayer::OnAttach()
{
  REGISTER_EVENT_CALLBACK(GLCore::MouseInputEvent, this, &TestLayer::OnMouseInputEvent);
}

void TestLayer::OnDetach()
{
  // todo add unregister callback
}

}  // namespace GLSandbox
