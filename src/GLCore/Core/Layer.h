#pragma once
#include <GLCore/Core/Timestep.h>

namespace GLCore {
class I_Layer {
 public:
  I_Layer(const char* name) : m_layerName(name){};
  virtual void OnAttach(){};
  virtual void OnDetach(){};
  virtual void OnUpdate(Timestep dt){};
  virtual void OnImGuiUpdate(Timestep dt){};
  virtual void OnFrameBegin(){};
  virtual void OnFrameEnd(){};

  // TODO events
  const char* GetName() { return m_layerName; };

  void SetEnabled(bool val);
  bool IsEnabled() const;

 protected:
  const char* m_layerName = "default";
  bool m_enabled = true;

 private:
};
}  // namespace GLCore
