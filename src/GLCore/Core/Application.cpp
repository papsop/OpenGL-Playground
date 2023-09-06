#include <GLCore/Core/Application.h>

namespace GLCore {
Application::Application()
{
  // ASSERT m_instance != nullptr
  InitGL();
  m_instance = this;
}

Application::~Application() {}

Application& Application::Instance()
{
  // ASSERT m_instance == nullptr
  return *m_instance;
}

void Application::InitGL()
{
  // ASSERT m_window == nullptr
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(800, 600, "OpenGL_Playground", NULL, NULL);
  // ASSERT m_window == nullptr
  glfwMakeContextCurrent(m_window);
  // glfwSetFramebufferSizeCallback()

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    // ASSERT failed to initialize glad
    // abort
  }
}
}  // namespace GLCore
