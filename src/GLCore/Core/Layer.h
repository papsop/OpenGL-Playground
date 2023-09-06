#pragma once

namespace GLCore {
class I_Layer {
 public:
  virtual void OnAttach(){};
  virtual void OnDetach(){};
  virtual void OnUpdate(float dt){};

 private:
};
}  // namespace GLCore
