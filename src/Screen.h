#pragma once

#include "ScreenType/IScreenType.h"

namespace ProtOS {
    class Screen {
    public:
        Screen();
        ~Screen();

        void OnUpdate(Timestep ts);
        void OnDraw(rgb_matrix::RGBMatrix* matrix);

        bool LoadConfig(const std::string& name);
        void SetScreenInfo(const std::string& name);

    private:
        nlohmann::json m_Config;
        std::vector<std::unique_ptr<IScreenType>> m_Screens;
    };
}