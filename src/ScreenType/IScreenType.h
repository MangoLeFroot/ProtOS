#pragma once

#include "../PCH.h"

namespace ProtOS {
    class IScreenType {
    public:
        virtual ~IScreenType() {}
        virtual void OnUpdate(Timestep ts) = 0;
        virtual void OnDraw(rgb_matrix::RGBMatrix* matrix) = 0;
    };
}