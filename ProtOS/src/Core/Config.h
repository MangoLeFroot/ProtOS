#pragma once

#include "PCH.h"

namespace ProtOS {
    class Config {
    public:
        static Config* GetInstance();
        nlohmann::json& operator[](const std::string& name);

        void Load(const std::string& name, const std::string& path);
    private:
        static Config* s_Instance;

        std::map<std::string, nlohmann::json> m_ConfigMap;
    };
}