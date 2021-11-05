#pragma once
#include "PCH.h"
#include "Screen.h"

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

        Screen* m_Face;

        bool m_Running;
        float m_LastFrameTime;

        Application();
        void OnUpdate();
        void OnDraw();
    };
}   