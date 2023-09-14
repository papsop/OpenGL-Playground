#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Core/LayerStack.h>

namespace GLCore {
class Application;

class AppControlOverlay : public I_Layer {
 public:
  AppControlOverlay() : I_Layer("Application control", true){};

  void OnAttach() override;
  void OnDetach() override;

  void OnFrameBegin() override;
  void OnUpdate(Timestep dt) override;
  void OnImGuiUpdate(Timestep dt) override;
  void OnFrameEnd() override;

 private:
  Application* m_application;
  LayerStack* m_layerStack;
  size_t m_fpsValueOffset = 0;  // for wrapping
  float m_fpsValues[144] = {};
};
}  // namespace GLCore
