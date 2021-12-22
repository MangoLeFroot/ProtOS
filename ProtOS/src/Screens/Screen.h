#pragma once

#include "ScreenType/IScreenType.h"

// Delta time
#include "../Core/Timestep.h"

namespace ProtOS {
    class Screen {
    public:
        Screen(const std::string& name);
        ~Screen();

        void OnUpdate(Timestep ts);
        void OnDraw(rgb_matrix::FrameCanvas* canvas);
        void SetScreenInfo(const std::string& name);

    private:
        std::string m_sConfigName;
        std::vector<std::unique_ptr<IScreenType>> m_Screens;
    };
}