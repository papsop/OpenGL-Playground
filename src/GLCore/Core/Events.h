#pragma once
#include <functional>
#include <vector>

namespace GLCore {

template <typename T>
class EventContainer {
 public:
  template <typename U>
  void AddListener(U* listener, void (U::*func)())
  {
    m_listeners.push_back([=]() { listener->*func() });
  }

  void RemoveListener(void* listener)
  {
    std::erase(std::remove_if(m_listeners.begin(), m_listeners.end(), [=](std::function<void()> func) { return func.target<void (*)()>() == listener; }),
               m_listeners.end());
  }

 private:
  std::vector<T> m_eventQueue;
  std::vector<std::function<void(T)>> m_listeners;
};

class EventDispatcher {
 public:
};

// =========================================
// GLCore events
// =========================================

struct GLCoreEvent {
  bool Handled = false;
  bool ImmediateEvent = false;  // Should we sent it instantly or wait til end of frame?
};

struct ApplicationEvent : public GLCoreEvent {
  bool TestData;
};

}  // namespace GLCore
