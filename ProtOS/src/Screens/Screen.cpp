#include "Screen.h"

#include "PCH.h"

#include "Core/Config.h"
#include "Screens/ScreenType/Image.h"
#include "Screens/ScreenType/Text.h"

namespace ProtOS {
    Screen::Screen(const std::string& name)
            : m_sConfigName(name) {

    }
    
    Screen::~Screen() {
        // Clear out the m_Screens
        m_Screens.clear();
    }

    void Screen::OnUpdate(Timestep ts) {
        for (auto& screen : m_Screens) {
            screen->OnUpdate(ts);
        }
    }

    void Screen::OnDraw(rgb_matrix::FrameCanvas* canvas) {
        for (auto& screen : m_Screens) {
            screen->OnDraw(canvas);
        }
    }

    void Screen::SetScreenInfo(const std::string& name) {
        nlohmann::json screenInfo = (*Config::GetInstance())[m_sConfigName][name];

        // Clear out the m_Screens
        m_Screens.clear();

        // Load screen type and push into m_Screen
        for(auto& info : screenInfo) {
            std::string type(info["type"]);
            if (type == "image") {
                std::unique_ptr<ScreenImage> screenImage = std::make_unique<ScreenImage>(info);
                m_Screens.push_back(std::move(screenImage));
            } else if (type == "text") {
                std::unique_ptr<ScreenText> screenText = std::make_unique<ScreenText>(info);
                m_Screens.push_back(std::move(screenText));
            } else {

            }
        }
    }
}