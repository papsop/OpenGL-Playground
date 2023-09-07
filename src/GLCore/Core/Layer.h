#pragma once

namespace GLCore {
class I_Layer {
 public:
  virtual void OnAttach(){};
  virtual void OnDetach(){};
  virtual void OnUpdate(float dt){};

  const char* GetName() { return m_layerName; };

 protected:
  const char* m_layerName;

 private:
};
}  // namespace GLCore
