#pragma once
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <memory>

namespace GLCore {
class Log {
 public:
  using ptr_Logger = std::shared_ptr<spdlog::logger>;

  static void Init();
  inline static ptr_Logger& GetLogger() { return m_logger; };

 private:
  inline static ptr_Logger m_logger = nullptr;
};
}  // namespace GLCore

#define LOG_DEBUG(...) GLCore::Log::GetLogger()->trace(##__VA_ARGS__)
#define LOG_INFO(...) GLCore::Log::GetLogger()->info(##__VA_ARGS__)
#define LOG_WARN(...) GLCore::Log::GetLogger()->warn(##__VA_ARGS__)
#define LOG_ERROR(...) GLCore::Log::GetLogger()->error(##__VA_ARGS__)
#define LOG_FATAL(...)                            \
  GLCore::Log::GetLogger()->error(##__VA_ARGS__); \
  abort();

#define GL_ASSERT(exp, ...)   \
  if (!(exp)) {               \
    LOG_ERROR(##__VA_ARGS__); \
    abort();                  \
  }
