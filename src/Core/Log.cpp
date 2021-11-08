#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace ProtOS {
    std::unique_ptr<std::map<std::string, std::shared_ptr<spdlog::logger>>> Log::s_LoggerMap;

    void Log::Init() {
        s_LoggerMap = std::make_unique<std::map<std::string, std::shared_ptr<spdlog::logger>>>();
        spdlog::set_pattern("%^[%T] %n: %v%$");
    }

    void Log::AddLogger(const std::string& name) {
        std::shared_ptr<spdlog::logger> logger = spdlog::stdout_color_mt(name);
        logger->set_level(spdlog::level::trace);
        s_LoggerMap->insert(std::make_pair(name, logger));

        PROTOS_LOG_INFO("ProtOS", "Logger registered: {0}", name);
    }
}