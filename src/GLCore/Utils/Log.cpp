#include <GLCore/Utils/Log.h>

namespace GLCore {

void Log::Init()
{
  if (m_logger != nullptr) return;  // assert?

  m_logger = spdlog::stdout_color_mt("GLCore");
  m_logger->set_level(spdlog::level::trace);
  LOG_DEBUG("Initializing Logger");
}

}  // namespace GLCore
