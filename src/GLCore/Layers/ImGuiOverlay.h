#pragma once
#include <GLCore/Core/Layer.h>

namespace GLCore {
class ImGuiOverlay : public I_Layer {
 public:
  ImGuiOverlay() : I_Layer("ImGui"){};
  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate(Timestep dt) override;
  void OnImGuiUpdate(Timestep dt) override;

  void BeginImGuiFrame();
  void EndImGuiFrame();

 private:
};
}  // namespace GLCore
