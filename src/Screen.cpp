#include "PCH.h"
#include "Screen.h"

#include "ScreenType/ScreenImage.h"

namespace ProtOS {
    Screen::Screen() {

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

    void Screen::OnDraw(rgb_matrix::RGBMatrix* matrix) {
        for (auto& screen : m_Screens) {
            screen->OnDraw(matrix);
        }
    }

    bool Screen::LoadConfig(const std::string& name) {
        std::ifstream stream(name);
        if(!stream)
            return false;

        stream >> m_Config;
        stream.close();
        return true;
    }

    void Screen::SetScreenInfo(const std::string& name) {
        nlohmann::json screenInfo = m_Config[name];

        // Clear out the m_Screens
        m_Screens.clear();

        // Load screen type and push into m_Screen
        for(auto& info : screenInfo) {
            std::string type(info["type"]);
            if (type == "image") {
                std::unique_ptr<ScreenImage> screenImage = std::make_unique<ScreenImage>();
                m_Screens.push_back(std::move(screenImage));
            } else if (type == "text") {

            } else {

            }
        }
    }
}