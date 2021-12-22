#pragma once

#include "PCH.h"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

namespace ProtOS {
    class StaticController : public oatpp::web::server::api::ApiController {
    public:
        StaticController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
                : oatpp::web::server::api::ApiController(objectMapper) {}

    public:
        ENDPOINT("GET", "/", root) {
            const char *html =
                    "<html lang='en'>"
                    "  <head>"
                    "    <meta charset=utf-8/>"
                    "  </head>"
                    "  <body>"
                    "    <p>Hello CRUD example project!</p>"
                    "    <a href='swagger/ui'>Checkout Swagger-UI page</a>"
                    "  </body>"
                    "</html>";
            auto response = createResponse(Status::CODE_200, html);
            response->putHeader(Header::CONTENT_TYPE, "text/html");
            return response;
        }

    };
}

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen