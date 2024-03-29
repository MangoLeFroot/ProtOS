#include "Application.h"

#include <ctime>

#include "Core/Config.h"
#include "Core/Log.h"
#include "Core/Timestep.h"


using namespace rgb_matrix;

namespace ProtOS
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
            : m_Running(false){
#ifdef USE_MATRIX
        // Configure and initialize the matrices.
        RGBMatrix::Options options;
        RuntimeOptions runtime_opt;

        options.hardware_mapping = "adafruit-hat-pwm";
        options.cols = 64;
        options.rows = 32;
        options.chain_length = 2;
        options.parallel = 1;
        options.led_rgb_sequence = "BRG";
        options.limit_refresh_rate_hz = 90;
        options.show_refresh_rate = true;

        m_Matrix = RGBMatrix::CreateFromOptions(options, runtime_opt);
        if(!m_Matrix) PROTOS_LOG_FATAL("ProtOS", "Failed to initialize matrix.");

        m_Canvas = m_Matrix->CreateFrameCanvas();
#endif

        Config::GetInstance()->Load("face", "./config/faces.json");

        m_Face = new Screen("face");
        m_Face->SetScreenInfo("booting");

        m_LastFrameTime = clock();
    }

    Application::~Application() {
        m_Matrix->Clear();
        delete m_Matrix;
    }

    Application* Application::GetInstance() {
        if (s_Instance == nullptr)
            s_Instance = new Application();

        return s_Instance;
    }

    void Application::Run() {
        m_Running = true;

        while(m_Running) {
            OnUpdate();
            OnDraw();
        }
    }

    void Application::Stop() {
        m_Running = false;
    }

    void Application::OnUpdate() {
        long time = clock();
        Timestep timestep = (time - m_LastFrameTime) / CLOCKS_PER_SEC;
        m_LastFrameTime = time;

        //std::fprintf(stderr, "FPS: %d\n", (int)(CLOCKS_PER_SEC / (time - m_LastFrameTime)));

        m_Face->OnUpdate(timestep);
    }

    void Application::OnDraw() {
#ifdef USE_MATRIX
        m_Face->OnDraw(m_Canvas);
        m_Canvas = m_Matrix->SwapOnVSync(m_Canvas);
#endif
    }
}
