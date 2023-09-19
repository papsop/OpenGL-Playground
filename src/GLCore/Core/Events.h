#pragma once
#include <GLCore/Utils/IDGenerator.h>
#include <GLCore/Utils/Log.h>

#include <functional>
#include <vector>
#include <utility>
#include <memory>

namespace GLCore {

// =======================================================
// Base for all events
struct GLCoreEventBase {
  bool Handled = false;
  bool Immediate = false;  // Should we sent it instantly or wait until end of frame processing?
};

// =======================================================
// EVENT CONTAINER
// =======================================================
class EventContainerBase {
 public:
  virtual ~EventContainerBase() = default;
};

template <typename T, typename = std::enable_if_t<std::is_base_of_v<GLCoreEventBase, T>>>
class EventContainer : public EventContainerBase {
 public:
  using EventCallback = std::function<void(const T&)>;

  ~EventContainer() override
  {
    m_eventQueue.clear();
    m_listeners.clear();
  }
  // Keep this here, I don't know how to put it into .inl file, since Class T and Function U are different /shrug
  void AddListener(void* listener, EventCallback func)
  {
    m_listeners.insert({listener, func});
  }

  void RemoveListener(void* listener)
  {
    // todo
  }

  void AddEvent(T event)
  {
    if (event.Immediate)
      ProcessEvent(event);
    else
      m_eventQueue.push_back(event);
  }
  void ProcessEvent(T Event)
  {
    if (event.Handled) return;

    for (auto& func : m_listeners) {
      func(event);
    }
    event.Handled = true;
  }

  void ProcessAllEvents()
  {
    for (auto T& event : m_eventQueue) {
      ProcessEvent(event);
    }
    m_eventQueue.clear();
  }

 private:
  std::vector<T> m_eventQueue;
  std::unordered_map<void*, EventCallback> m_listeners;
};

// =======================================================
// EVENT DISPATCHER
// =======================================================
class EventDispatcher {
 public:
  ~EventDispatcher()
  {
    m_eventContainers.clear();
  }

  template <typename T, typename... Args>
  void RegisterListener(void* listener, std::function<void(const T&)> func)
  {
    size_t containerID = IDGenerator<GLCoreEventBase>::GetID<T>();

    if (m_eventContainers.find(containerID) == m_eventContainers.end()) {
      // No container yet, create a new one
      std::unique_ptr<EventContainerBase> container = std::make_unique<EventContainer<T>>();
      m_eventContainers.insert({containerID, std::move(container)});
    }

    EventContainer<T>* container = static_cast<EventContainer<T>*>(m_eventContainers[containerID].get());
    container->AddListener(listener, func);
    LOG_WARN("Registering listener");
  }

 private:
  std::unordered_map<size_t, std::unique_ptr<EventContainerBase>> m_eventContainers;
};

// =========================================
// GLCore events
// =========================================

struct ApplicationEvent : public GLCoreEventBase {
  bool TestData;
};

}  // namespace GLCore

#define GL_BIND_FUNCTION_1(instance, function) std::bind(function, instance, std::placeholders::_1)

#define REGISTER_EVENT_CALLBACK(eventType, instance, function)                                                                          \
  {                                                                                                                                     \
    Application::Instance().GetEventDispatcher()->RegisterListener<eventType>((void*)instance, GL_BIND_FUNCTION_1(instance, function)); \
  }

// m_eventDispatcher->RegisterListener<ApplicationEvent>((void*)this, std::bind(&Application::OnApplicationEvent, this, std::placeholders::_1));
