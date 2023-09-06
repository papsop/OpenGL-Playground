#include <GLCore/Core/Application.h>
#include <GLCore/Utils/Log.h>

namespace GLCore {
Application::Application()
{
  GL_ASSERT(m_instance == nullptr, "Application already has an instance");
  Log::Init();
  InitGL();
  m_instance = this;
}

Application::~Application() {}

Application& Application::Instance() { return *m_instance; }

void Application::InitGL()
{
  LOG_DEBUG("Initializing Application");

  GL_ASSERT(m_window == nullptr, "Application already created a window");
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(800, 600, "OpenGL_Playground", NULL, NULL);
  GL_ASSERT(m_window != nullptr, "Unable to create a GLFW window");

  glfwMakeContextCurrent(m_window);
  // glfwSetFramebufferSizeCallback()

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    GL_ASSERT(false, "Unable to initialize GLAD");
  }
}
}  // namespace GLCore
