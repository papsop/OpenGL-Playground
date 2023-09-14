#include <GLCore/Layers/TriangleTestLayer.h>
#include <GLCore/Utils/Log.h>
#include <GLCore/Core/Application.h>

#include <imgui.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace GLCore {

void TriangleTestLayer::OnAttach()
{
  // Path goes from /projects/ folder, I fucking hate this environment
  m_shader.LoadShadersFromFiles("../assets/shaders/shader.vert.glsl", "../assets/shaders/shader.frag.glsl");
}

void TriangleTestLayer::OnDetach()
{
}

void TriangleTestLayer::OnUpdate(Timestep dt)
{
  Application::Instance().GetRenderer()->DrawLine({1.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});
  Application::Instance().GetRenderer()->DrawLine({-1.0f, -1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});
}

void TriangleTestLayer::OnImGuiUpdate(Timestep dt)
{
}

}  // namespace GLCore
