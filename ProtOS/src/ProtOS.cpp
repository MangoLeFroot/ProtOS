#include "Core/Application.h"
#include "Core/Log.h"
#include "REST/Component/App.h"
#include "REST/Controller/Face.h"
#include "REST/Controller/Static.h"

#include <signal.h>

using namespace ProtOS;

Application* app = nullptr;
std::atomic_bool server_should_continue(true);

static void InterruptHandler(int signo) {
    PROTOS_LOG_INFO("ProtOS", "Stopping...");
    app->Stop();
}


int main(int argc, char *argv[]) {
    Magick::InitializeMagick(*argv);

    // setup signal processing
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    Log::Init();
    Log::AddLogger("ProtOS");
    PROTOS_LOG_INFO("ProtOS", "Initialized Log!");

    oatpp::base::Environment::init();

    /* Register components in scope of run() */
    AppComponent components;

    /* Get router component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

    /* Create MyController and add all of its endpoints to router */
    oatpp::web::server::api::Endpoints docEndpoints;
    docEndpoints.append(router->addController(std::make_shared<FaceController>())->getEndpoints());

    router->addController(oatpp::swagger::Controller::createShared(docEndpoints));
    router->addController(std::make_shared<StaticController>());

    /* Get connection handler component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

    /* Get connection provider component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

    /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
    oatpp::network::Server server(connectionProvider, connectionHandler);

    std::thread oatppThread([&server] {

        /* Run server, let it check a lambda-function if it should continue to run
         * Return true to keep the server up, return false to stop it.
         * Treat this function like a ISR: Don't do anything heavy in it! Just check some flags or at max some very
         * lightweight logic.
         * The performance of your REST-API depends on this function returning as fast as possible! */
        std::function<bool()> condition = [](){
            return server_should_continue.load();
        };

        server.run(condition);
    });

    /* Print info about server port */
    PROTOS_LOG_INFO("ProtOS", "Server running on port {0}", static_cast<const char*>(connectionProvider->getProperty("port").getData()));

    // Launch ProtOS Application
    app = Application::GetInstance();

    if(app != nullptr)
        app->Run();
    delete app; // App exit

    /* First, stop the ServerConnectionProvider so we don't accept any new connections */
    connectionProvider->stop();

    /* Signal the stop condition */
    server_should_continue.store(false);

    /* Finally, stop the ConnectionHandler and wait until all running connections are closed */
    connectionHandler->stop();

    /* Check if the thread has already stopped or if we need to wait for the server to stop */
    if(oatppThread.joinable()) {

        /* We need to wait until the thread is done */
        oatppThread.join();
    }

    oatpp::base::Environment::destroy();

    return EXIT_SUCCESS;
}