#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Core/LayerStack.h>

namespace GLCore {
class AppControlOverlay : public I_Layer {
 public:
  AppControlOverlay() : I_Layer("AppControl", true){};

  void OnAttach() override;
  void OnDetach() override;

  void OnFrameBegin() override;
  void OnUpdate(Timestep dt) override;
  void OnImGuiUpdate(Timestep dt) override;
  void OnFrameEnd() override;

 private:
  LayerStack* m_layerStack;
};
}  // namespace GLCore
