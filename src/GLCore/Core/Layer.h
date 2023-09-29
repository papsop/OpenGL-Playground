#pragma once
#include <GLCore/Core/Timestep.h>

namespace GLCore {
class I_Layer {
 public:
  I_Layer(const char* name, bool enabled = true, bool locked = false) : m_layerName(name), m_enabled(enabled), m_isLocked(locked){};
  virtual void OnAttach(){};
  virtual void OnDetach(){};

  virtual void OnFrameBegin(){};
  virtual void OnUpdate(Timestep dt){};
  virtual void OnImGuiUpdate(Timestep dt){};
  virtual void OnFrameEnd(){};

  const char* GetName()
  {
    return m_layerName;
  };

  void SetEnabled(bool val);
  bool IsEnabled() const;
  bool IsLocked() const;
  bool ShouldUpdate() const;

 protected:
  const char* m_layerName = "unnamed";  // shows up in application control panel
  bool m_enabled = true;                // controls update
  const bool m_isLocked;                // always enabled, can't get disabled

 private:
};
}  // namespace GLCore
