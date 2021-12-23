#pragma once
#include "PCH.h"

#include "Core/Timestep.h"
#include "Screens/Type/IType.h"

namespace ProtOS {
    class ScreenText : virtual public IScreenType {
    public:
        ScreenText(nlohmann::basic_json<>& config);
        ~ScreenText();

        void OnUpdate(Timestep ts) override;
        void OnDraw(rgb_matrix::FrameCanvas* canvas) override;

    private:
        nlohmann::basic_json<> m_Config;
        int m_nIndex;
    };
}