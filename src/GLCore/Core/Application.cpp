#include <GLCore/Core/Application.h>
#include <GLCore/Core/Layer.h>
#include <GLCore/Layers/ImGuiOverlay.h>
#include <GLCore/Utils/Log.h>
#include <iostream>

namespace GLCore {
Application::Application()
{
  GL_ASSERT(m_instance == nullptr, "Application already has an instance");
  Initialize();
}

Application::~Application()
{
}

Application& Application::Instance()
{
  return *m_instance;
}

void Application::Initialize()
{
  Log::Init();
  LOG_INFO("Initializing Application");
  InitGL();
  m_instance = this;
}

void Application::InitGL()
{
  GL_ASSERT(m_window == nullptr, "Application already created a window");
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(800, 600, "OpenGL_Playground", NULL, NULL);
  GL_ASSERT(m_window != nullptr, "Unable to create a GLFW window");
  LOG_DEBUG("GLFW Initialized");

  glfwMakeContextCurrent(m_window);
  // glfwSetFramebufferSizeCallback()

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    GL_ASSERT(false, "Unable to initialize GLAD");
  }
  LOG_DEBUG("GLAD Initialized");

  glfwSetWindowCloseCallback(m_window, Application::window_close_callback);
  glViewport(0, 0, 800, 600);

  LOG_INFO("Application initialized");
}

void Application::window_close_callback(GLFWwindow* window)
{
  m_isRunning = false;
}

GLFWwindow* Application::GetWindow()
{
  return m_window;
}

void Application::Run()
{
  GL_ASSERT(m_window != nullptr, "Can't run application without initializing it first");

  m_imGuiOverlay = new ImGuiOverlay();
  m_layerStack.PushOverlay(m_imGuiOverlay);

  while (m_isRunning) {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
  }

  glfwTerminate();
}

}  // namespace GLCore
