#pragma once

#include "../../PCH.h"

// Delta time
#include "../../Core/Timestep.h"


namespace ProtOS {
    class IScreenType {
    public:
        virtual ~IScreenType() {}
        virtual void OnUpdate(Timestep ts) = 0;
        virtual void OnDraw(rgb_matrix::FrameCanvas* canvas) = 0;
    };
}