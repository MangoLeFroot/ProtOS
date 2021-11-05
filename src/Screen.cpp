#include "PCH.h"
#include "Screen.h"

#include "ScreenType/ScreenImage.h"

namespace ProtOS {
    Screen::Screen() {

    }
    
    Screen::~Screen() {
        // Clear out the m_Screens
        for(auto& screen : m_Screens) delete screen;
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
        for(auto& screen : m_Screens) delete screen;
        m_Screens.clear();

        // Load screen type and push into m_Screen
        for(auto& info : screenInfo) {
            std::string type(info["type"]);
            if (type == "image") {
                ScreenImage* screenImage = new ScreenImage();
                m_Screens.push_back(screenImage);
            } else if (type == "text") {

            } else {

            }
        }
    }
}