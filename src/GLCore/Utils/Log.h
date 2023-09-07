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

// TODO hide these when using Release build or nah?

#define LOG_DEBUG(...) SPDLOG_LOGGER_DEBUG(GLCore::Log::GetLogger(), ##__VA_ARGS__)
#define LOG_INFO(...) SPDLOG_LOGGER_INFO(GLCore::Log::GetLogger(), ##__VA_ARGS__)
#define LOG_WARN(...) SPDLOG_LOGGER_WARN(GLCore::Log::GetLogger(), ##__VA_ARGS__)
#define LOG_ERROR(...) SPDLOG_LOGGER_ERROR(GLCore::Log::GetLogger(), ##__VA_ARGS__)
#define LOG_FATAL(...)      \
  LOG_ERROR(##__VA_ARGS__); \
  abort();

#define GL_ASSERT(exp, ...)   \
  if (!(exp)) {               \
    LOG_ERROR(##__VA_ARGS__); \
    abort();                  \
  }
