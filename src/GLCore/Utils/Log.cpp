#include <GLCore/Utils/Log.h>

namespace GLCore {

void Log::Init()
{
  GL_TODO("Hide logger when compiling relase? Or implement an imgui console panel instead of using console application.");
  if (m_logger != nullptr) return;  // assert?

  m_logger = spdlog::stdout_color_mt("GLCore");
  m_logger->set_pattern("| %n | %-25s:%-5# | %^%-7l%$ | %v");
  m_logger->set_level(spdlog::level::trace);
  LOG_DEBUG("Initializing Logger");
}

}  // namespace GLCore
