#pragma once
#include <GLCore/Core/Layer.h>

namespace GLCore {

class ImGuiPanelRenderOverlay : public I_Layer {
 public:
  ImGuiPanelRenderOverlay() : I_Layer("Panel render")
  {
  }
  void OnAttach() override;
  void OnDetach() override;
  void OnFrameBegin() override;
  void OnImGuiUpdate(Timestep dt) override;
  void OnFrameEnd() override;

 private:
  void RescaleFrameBuffer(float width, float height);

  unsigned int m_width;
  unsigned int m_height;

  unsigned int m_FBO;
  unsigned int m_RBO;
  unsigned int m_texture;
};
}  // namespace GLCore
