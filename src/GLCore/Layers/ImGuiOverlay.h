#pragma once
#include <GLCore/Core/Layer.h>

namespace GLCore {
class ImGuiOverlay : public I_Layer {
 public:
  ImGuiOverlay() : I_Layer("ImGui", true, true){};
  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate(Timestep dt) override;
  void OnImGuiUpdate(Timestep dt) override;

  void OnFrameBegin() override;
  void OnFrameEnd() override;

 private:
  bool m_dockspaceInit = false;
};
}  // namespace GLCore
