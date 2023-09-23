#include <GLCore/Layers/ImGuiOverlay.h>
#include <GlCore/Core/Application.h>
#include <GLCore/Utils/Log.h>

#include <GLCore/Core/GLFWGlad.h>

#include <imgui.h>
#include <imgui_internal.h>
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

  // Global dockspace
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
  const ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);
  ImGui::SetNextWindowViewport(viewport->ID);
  window_flags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

  ImGui::Begin("Dockspace", NULL, window_flags);
  ImGuiID dockspace_id = ImGui::GetID("Dockspace");

  static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
  ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
  ImGui::End();

  //   if (!m_dockspaceInit) {
  //     // ImGui::DockBuilderRemoveNode(dockspace_id);
  //     ImGuiID dock1 = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.2f, nullptr, &dockspace_id);
  //     ImGuiID dock2 = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.8f, nullptr, &dockspace_id);
  //
  //     ImGui::DockBuilderDockWindow("Application control", dock1);
  //     ImGui::DockBuilderDockWindow("Sandbox canvas", dock2);
  //
  //     ImGui::DockBuilderFinish(dockspace_id);
  //     m_dockspaceInit = true;
  //   }
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
