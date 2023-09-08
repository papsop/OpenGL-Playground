#include <GLCore/Core/LayerStack.h>
#include <GLCore/Core/Layer.h>
#include <GLCore/Utils/Log.h>

namespace GLCore
{

LayerStack::LayerStack() : m_layers() {}

LayerStack::~LayerStack()
{
  for (auto* layer : m_layers)
  {
    layer->OnDetach();
    delete layer;
  }
}

void LayerStack::PushLayer(I_Layer* layer)
{
  LOG_INFO("Pushing layer '{0}'", layer->GetName());
  m_layers.emplace(m_layers.begin() + m_nextLayerIndex, layer);
  layer->OnAttach();
  m_nextLayerIndex++;
}

void LayerStack::PopLayer(I_Layer* layer)
{
  // TODO
}

void LayerStack::PushOverlay(I_Layer* overlay)
{
  LOG_INFO("Pushing overlay '{0}'", overlay->GetName());
  m_layers.emplace_back(overlay);
  overlay->OnAttach();
}

void LayerStack::PopOverlay(I_Layer*)
{
  // TODO
}

}  // namespace GLCore
