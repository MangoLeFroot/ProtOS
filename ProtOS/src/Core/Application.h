#pragma once
#include "PCH.h"
#include "Screens/Screen.h"

namespace ProtOS {
    class Application {
    public:
        static Application* GetInstance();
        ~Application();

        void Run();
        void Stop();

    private:
        static Application* s_Instance;

        rgb_matrix::RGBMatrix* m_Matrix;
        rgb_matrix::FrameCanvas* m_Canvas;

        Screen* m_Face;

        bool m_Running;
        long m_LastFrameTime;

        Application();
        void OnUpdate();
        void OnDraw();
    };
}   