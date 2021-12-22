#include "Config.h"

#include "Core/Log.h"

namespace ProtOS {
    Config* Config::s_Instance = nullptr;
    Config* Config::GetInstance() {
        if (s_Instance == nullptr)
            s_Instance = new Config();

        return s_Instance;
    }

    nlohmann::json& Config::operator[](const std::string& name) {
        if(m_ConfigMap.find(name) != m_ConfigMap.end())
            return m_ConfigMap[name];

        PROTOS_LOG_ERROR("ProtOS", "Invalid config: {0}", name);

        nlohmann::json empty;
        return empty ;
    }

    void Config::Load(const std::string& name, const std::string& path) {
        nlohmann::json conf;

        std::ifstream stream(path);
        if (!stream) {
            PROTOS_LOG_ERROR("ProtOS", "Failed to load config file: {0}", path);
            return;
        }

        stream >> conf;
        stream.close();

        m_ConfigMap[name] = conf;
    }

}