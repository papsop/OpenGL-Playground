#pragma once

namespace GLCore {

// helper class, that generates unique increasing IDs in given context, f.e. <Application>, <Events> etc.

template <typename _Context>
class IDGenerator {
 public:
  template <typename T>
  static size_t GetID()
  {
    static size_t ID = m_nextID++;
    return ID;
  }

 private:
  static size_t m_nextID;
};

template <typename _Context>
size_t IDGenerator<_Context>::m_nextID = 0;

}  // namespace GLCore
