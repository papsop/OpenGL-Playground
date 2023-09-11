#include <GLCore/Layers/ImGuiPanelRenderOverlay.h>
#include <GLCore/Utils/Log.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>

namespace GLCore {

void ImGuiPanelRenderOverlay::OnAttach()
{
  // Create a Frame buffer object
  glGenFramebuffers(1, &m_FBO);
  glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

  // Create a texture
  glGenTextures(1, &m_texture);
  glBindTexture(GL_TEXTURE_2D, m_texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

  // Create a render buffer object
  glGenRenderbuffers(1, &m_RBO);
  glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

  // if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) LOG_FATAL("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

  // unbind
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void ImGuiPanelRenderOverlay::OnDetach()
{
  glDeleteFramebuffers(1, &m_FBO);
  glDeleteTextures(1, &m_texture);
  glDeleteRenderbuffers(1, &m_RBO);
}

void ImGuiPanelRenderOverlay::OnFrameBegin()
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
  glViewport(0, 0, m_width, m_height);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ImGuiPanelRenderOverlay::OnFrameEnd()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ImGuiPanelRenderOverlay::RescaleFrameBuffer(float width, float height)
{
  m_width = width;
  m_height = height;

  glBindTexture(GL_TEXTURE_2D, m_texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

  glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
}

void ImGuiPanelRenderOverlay::OnImGuiUpdate(Timestep dt)
{
  ImGui::Begin("Render window");

  float width = ImGui::GetContentRegionAvail().x;
  float height = ImGui::GetContentRegionAvail().y;

  RescaleFrameBuffer(width, height);

  ImGui::Image((void*)m_texture, ImVec2(m_width, m_height), ImVec2(0, 1), ImVec2(1, 0));

  ImGui::End();
}

}  // namespace GLCore
