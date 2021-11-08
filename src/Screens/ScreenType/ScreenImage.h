#pragma once

#include "../../PCH.h"

// Delta time
#include "../../Core/Timestep.h"


#include "IScreenType.h"

namespace ProtOS {
    class ScreenImage: virtual  public IScreenType {
    public:
        void OnUpdate(Timestep ts);
        void OnDraw(rgb_matrix::RGBMatrix* matrix);
    };
}