#pragma once
#include <GLCore/Core/Layer.h>
#include <GLCore/Core/Renderer.h>

namespace GLCore {
class RendererControlLayer : public I_Layer {
 public:
  RendererControlLayer() : I_Layer("Renderer controller")
  {
  }
  void OnImGuiUpdate(Timestep dt) override;

  void OnAttach() override;

 private:
  Renderer2D* m_renderer;
};
}  // namespace GLCore
