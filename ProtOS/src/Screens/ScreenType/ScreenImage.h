#pragma once
#include <CImg.h>

#include "PCH.h"

// Delta time
#include "Core/Timestep.h"


#include "IScreenType.h"

namespace ProtOS {
    class ScreenImage: virtual  public IScreenType {
    public:
        ScreenImage(const nlohmann::basic_json<>& config);
        ~ScreenImage();

        void OnUpdate(Timestep ts);
        void OnDraw(rgb_matrix::FrameCanvas* canvas);

    private:
        int m_nFrame;
        cimg_library::CImg<uint8_t>* m_Image;
    };
}
