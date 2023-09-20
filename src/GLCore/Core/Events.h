#pragma once
#include <GLCore/Utils/IDGenerator.h>
#include <GLCore/Utils/Log.h>

#include <glm/vec2.hpp>

#include <functional>
#include <vector>
#include <utility>
#include <memory>

namespace GLCore {

// =======================================================
// Base for all events
struct GLCoreEventBase {
  GLCoreEventBase() = default;
  GLCoreEventBase(bool immediate) : Immediate(Immediate)
  {
  }

  bool Handled = false;
  bool Immediate = false;  // Should we sent it instantly or wait until end of frame processing?
};

// =======================================================
// EVENT CONTAINER
// =======================================================
class EventContainerBase {
 public:
  virtual ~EventContainerBase() = default;
  virtual void ProcessAllEvents() = 0;
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
  void ProcessEvent(T event)
  {
    if (event.Handled) return;

    for (const auto& [listener, function] : m_listeners) {
      function(event);
    }
    event.Handled = true;
  }

  void ProcessAllEvents() override
  {
    for (const T& event : m_eventQueue) {
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
  }

  template <typename T>
  void Dispatch(T event)
  {
    size_t containerID = IDGenerator<GLCoreEventBase>::GetID<T>();

    if (m_eventContainers.find(containerID) == m_eventContainers.end()) return;  // no listeners
    EventContainer<T>* container = static_cast<EventContainer<T>*>(m_eventContainers[containerID].get());
    container->AddEvent(event);
  }

  void ProcessAllEvents()
  {
    for (auto& container : m_eventContainers) {
      container.second->ProcessAllEvents();
    }
  }

 private:
  std::unordered_map<size_t, std::unique_ptr<EventContainerBase>> m_eventContainers;
};

// =========================================
// GLCore events
// =========================================

struct ApplicationEvent : public GLCoreEventBase {
  enum EventType {
    Close,
  };

  EventType Type;
};

struct WindowEvent : public GLCoreEventBase {
  enum EventType {
    Close,
  };

  EventType Type;
};

struct SandboxCanvasMouseEvent : public GLCoreEventBase {
  enum EventType {
    Hover,
    LeftClickPressed,
    LeftClickReleased,
    RightClickPressed,
    RightClickReleased,
  };

  SandboxCanvasMouseEvent(EventType type, glm::vec2 pos, bool immediate) : GLCoreEventBase(immediate), Type(type), Position(pos)
  {
  }

  EventType Type;
  glm::vec2 Position;
};

struct SandboxCanvasEvent : public GLCoreEventBase {
  enum EventType {
    Resize,
  };

  EventType Type;
  union {
    glm::vec2 NewSize;
  } Data;

  SandboxCanvasEvent(EventType type) : Type(type){};
};

}  // namespace GLCore

// =========================================
// Helper macros
// =========================================
#define GL_BIND_FUNCTION_1(instance, function) std::bind(function, instance, std::placeholders::_1)

#define REGISTER_EVENT_CALLBACK(eventType, instance, function)                                                                                  \
  {                                                                                                                                             \
    GLCore::Application::Instance().GetEventDispatcher()->RegisterListener<eventType>((void*)instance, GL_BIND_FUNCTION_1(instance, function)); \
  }

#define DISPATCH_EVENT(event)                                              \
  {                                                                        \
    GLCore::Application::Instance().GetEventDispatcher()->Dispatch(event); \
  }

// m_eventDispatcher->RegisterListener<ApplicationEvent>((void*)this, std::bind(&Application::OnApplicationEvent, this, std::placeholders::_1));
