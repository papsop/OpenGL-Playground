#include <GLCore/Platform/WindowsWindow.h>
#include <GLCore/Utils/Log.h>

namespace GLCore {

WindowsWindow::~WindowsWindow()
{
  if (m_window) {
    Destroy();
  }
}

void WindowsWindow::Init(WindowDef def)
{
  if (m_window) {
    Destroy();
  }
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(def.Width, def.Height, def.Title.c_str(), NULL, NULL);
  GL_ASSERT(m_window != nullptr, "Unable to create a GLFW window");
  LOG_DEBUG("GLFW Initialized");

  glfwMakeContextCurrent(m_window);
  // glfwSetFramebufferSizeCallback()

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    GL_ASSERT(false, "Unable to initialize GLAD");
  }
  LOG_DEBUG("GLAD Initialized");

  glViewport(0, 0, def.Width, def.Height);
  LOG_DEBUG("OpenGL Info:");
  LOG_DEBUG("  Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));  // imagine just returning a fucking const char*
  LOG_DEBUG("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
  LOG_DEBUG("  Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

  LOG_INFO("WindowsWindow created");
}

void WindowsWindow::Destroy()
{
  glfwDestroyWindow(m_window);
  glfwTerminate();
  m_window = nullptr;
  LOG_INFO("WindowsWindow destroyed");
}

void WindowsWindow::Update(Timestep ts)
{
  LOG_DEBUG("{0}", ts.GetMilliseconds());
  glfwSwapBuffers(m_window);
  glfwPollEvents();
}

uint32_t WindowsWindow::GetWidth() const
{
  return 0;  // might need to hold the info inside this class, because GLFWwindow is an opaque pointer
}

uint32_t WindowsWindow::GetHeight() const
{
  return 0;
}

}  // namespace GLCore
