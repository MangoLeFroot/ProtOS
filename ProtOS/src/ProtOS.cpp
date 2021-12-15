#include "Core/Application.h"

#include <signal.h>

using namespace ProtOS;

Application* app = nullptr;

static void InterruptHandler(int signo) {
    app->Stop();
}

int main(int argc, char *argv[]) {
    Magick::InitializeMagick(*argv);

    // setup signal processing
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);


    app = Application::GetInstance();

    if(app == nullptr)
        return EXIT_FAILURE;

    app->Run();

    delete app;
    return EXIT_SUCCESS;
}