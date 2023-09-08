#include <GLCore/Layers/ImGuiOverlay.h>
#include <GlCore/Core/Application.h>
#include <GLCore/Utils/Log.h>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace GLCore {

void ImGuiOverlay::OnAttach()
{
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    // Enable Multi-Viewport / Platform Windows

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  Application& app = Application::Instance();
  GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow()->GetVoidWindow());

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 410");

  LOG_INFO("ImGui initialized");
}

void ImGuiOverlay::OnDetach()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void ImGuiOverlay::OnUpdate(Timestep dt)
{
}

void ImGuiOverlay::OnImGuiUpdate(Timestep dt)
{
}

void ImGuiOverlay::OnFrameBegin()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void ImGuiOverlay::OnFrameEnd()
{
  ImGuiIO& io = ImGui::GetIO();
  io.DisplaySize = ImVec2(1280, 720);

  // Rendering
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }
}

}  // namespace GLCore
