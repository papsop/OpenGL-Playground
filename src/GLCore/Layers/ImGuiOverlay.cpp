#include <GLCore/Layers/ImGuiOverlay.h>
#include <GlCore/Core/Application.h>
#include <GLCore/Utils/Log.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace GLCore {
void ImGuiOverlay::OnAttach()
{
  //   // Setup Dear ImGui context
  //   IMGUI_CHECKVERSION();
  //   ImGui::CreateContext();
  //
  //   ImGuiIO& io = ImGui::GetIO();
  //   io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  //   io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable Docking
  //   io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    // Enable Multi-Viewport / Platform Windows
  //
  //   // Setup Dear ImGui style
  //   ImGui::StyleColorsDark();
  //
  //   // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
  //   ImGuiStyle& style = ImGui::GetStyle();
  //   if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
  //     style.WindowRounding = 0.0f;
  //     style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  //   }
  //
  //   Application& app = Application::Instance();
  //   GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow());
  //
  //   // Setup Platform/Renderer bindings
  //   ImGui_ImplGlfw_InitForOpenGL(window, true);
  //   ImGui_ImplOpenGL3_Init("#version 410");
  //
  //   LOG_INFO("ImGui initialized");
}

void ImGuiOverlay::OnDetach()
{
  //   ImGui_ImplOpenGL3_Shutdown();
  //   ImGui_ImplGlfw_Shutdown();
  //   ImGui::DestroyContext();
}

void ImGuiOverlay::OnUpdate(Timestep dt)
{
}

void ImGuiOverlay::OnImGuiUpdate(Timestep dt)
{
}

void ImGuiOverlay::OnFrameBegin()
{
}

void ImGuiOverlay::OnFrameEnd()
{
}

}  // namespace GLCore
