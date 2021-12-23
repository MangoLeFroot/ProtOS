#pragma once
#include "PCH.h"

#include "Core/Timestep.h"
#include "Screens/ScreenType/IType.h"

namespace ProtOS {
    class ScreenImage: virtual  public IScreenType {
    public:
        ScreenImage(nlohmann::basic_json<>& config);
        ~ScreenImage();

        void OnUpdate(Timestep ts) override;
        void OnDraw(rgb_matrix::FrameCanvas* canvas) override;

    private:
        nlohmann::basic_json<> m_Config;

        bool m_bHasAlpha = false;

        float m_fLastFrameTime = 0.0f;
        int m_nFrame = 0;

        std::vector<Magick::Image> m_Images;

        bool HasAlpha(const Magick::Image& image);
    };
}
