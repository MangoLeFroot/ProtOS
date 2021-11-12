#pragma once

#include "PCH.h"
#include "spdlog/spdlog.h"

namespace ProtOS {
    class Log {
    public:
        static void Init();
        
        static void AddLogger(const std::string& name);
        static std::shared_ptr<spdlog::logger>& GetLogger(const std::string& name) { return s_LoggerMap->at(name); }

    private:
        static std::unique_ptr<std::map<std::string, std::shared_ptr<spdlog::logger>>> s_LoggerMap;
    };
}

// Logging macros
#define PROTOS_LOG_TRACE(NAME, ...) ProtOS::Log::GetLogger(NAME)->trace(__VA_ARGS__)
#define PROTOS_LOG_INFO(NAME, ...)  ProtOS::Log::GetLogger(NAME)->info(__VA_ARGS__)
#define PROTOS_LOG_WARN(NAME, ...)  ProtOS::Log::GetLogger(NAME)->warn(__VA_ARGS__)
#define PROTOS_LOG_ERROR(NAME, ...) ProtOS::Log::GetLogger(NAME)->error(__VA_ARGS__)
#define PROTOS_LOG_FATAL(NAME, ...) ProtOS::Log::GetLogger(NAME)->fatal(__VA_ARGS__)