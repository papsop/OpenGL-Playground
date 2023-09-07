#pragma once
#include <vector>

namespace GLCore {
class I_Layer;

/*
 * Data structure that holds layers and overlays, Layers always come before Overlays
 * - holds index of the last layer so it knows where to place next one
 */
class LayerStack {
 public:
  LayerStack();
  ~LayerStack();
  void PushLayer(I_Layer*);
  void PopLayer(I_Layer*);

  void PushOverlay(I_Layer*);
  void PopOverlay(I_Layer*);

 private:
  std::vector<I_Layer*> m_layers;
  size_t m_nextLayerIndex = 0;
};
}  // namespace GLCore
