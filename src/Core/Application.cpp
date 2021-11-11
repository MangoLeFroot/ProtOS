#include "Application.h"

// Delta time
#include "Timestep.h"

// Logging
#include "Log.h"


#include <ctime>

using namespace rgb_matrix;

namespace ProtOS
{
    Application* Application::s_Instance = nullptr;

    Application::Application() {
      Log::Init();
      Log::AddLogger("ProtOS");
      PROTOS_LOG_INFO("ProtOS", "Initialized Log!");

      // Configure and initialize the matrices.
      RGBMatrix::Options options;
      RuntimeOptions runtime_opt;

      options.hardware_mapping = "adafruit-hat-pwm";
      options.cols = 64;
      options.rows = 32;
      options.chain_length = 2;
      options.parallel = 1;
      options.led_rgb_sequence = "BRG";

      m_Matrix = RGBMatrix::CreateFromOptions(options, runtime_opt);
      assert(m_Matrix);

      m_Canvas = m_Matrix->CreateFrameCanvas();

      m_Face = new Screen();
      assert(m_Face->LoadConfig("./config/booting.json"));

      m_Face->SetScreenInfo("booting");
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
        float time = clock();
        Timestep timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;

        std::fprintf(stderr, "FPS: %d\n", (int)(CLOCKS_PER_SEC / timestep.GetSeconds()));

        m_Face->OnUpdate(timestep);
    }

    void Application::OnDraw() {
        m_Face->OnDraw(m_Canvas);
        m_Canvas = m_Matrix->SwapOnVSync(m_Canvas);
    }
}
