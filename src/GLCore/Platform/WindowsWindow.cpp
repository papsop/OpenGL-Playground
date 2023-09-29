#include <GLCore/Platform/WindowsWindow.h>
#include <GLCore/Utils/Log.h>
#include <GLCore/Core/Application.h>
#include <GLCore/Core/Events.h>

namespace GLCore {
// =============================================================
// Static callbacks for GLFW (it doesn't support c++ function, have to do it C style)
static void window_close_callback(GLFWwindow* window)
{
  glfwSetWindowShouldClose(window, GLFW_FALSE);
  E_WindowEvent e;
  e.Type = E_WindowEvent::Close;

  DISPATCH_EVENT(e);
}

static void opengl_error_callback(int error_code, const char* description)
{
  LOG_ERROR(description);
}

// =============================================================
WindowsWindow::~WindowsWindow()
{
  if (m_window) {
    Destroy();
  }
}

void WindowsWindow::Init(WindowDef def /*= WindowDef()*/)
{
  if (m_window) {
    Destroy();
  }
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

  m_window = glfwCreateWindow(def.Width, def.Height, def.Title.c_str(), NULL, NULL);
  GL_ASSERT(m_window != nullptr, "Unable to create a GLFW window");
  LOG_DEBUG("GLFW Initialized");

  glfwMakeContextCurrent(m_window);

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
  SetVSync(m_vSyncEnabled);

  glfwSetWindowCloseCallback(m_window, window_close_callback);
  glfwSetErrorCallback(opengl_error_callback);
}

void* WindowsWindow::GetVoidWindow()
{
  return m_window;
}

void WindowsWindow::OnFrameBegin()
{
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void WindowsWindow::OnFrameEnd()
{
  glfwPollEvents();
  glfwSwapBuffers(m_window);
}

bool WindowsWindow::IsVSync()
{
  return m_vSyncEnabled;
}

void WindowsWindow::SetVSync(bool val)
{
  // if (val == m_vSyncEnabled) return;  // ignore call

  if (val)
    glfwSwapInterval(1);
  else
    glfwSwapInterval(0);

  m_vSyncEnabled = val;
}

void WindowsWindow::Destroy()
{
  glfwDestroyWindow(m_window);
  glfwTerminate();
  m_window = nullptr;
  LOG_INFO("WindowsWindow destroyed");
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
