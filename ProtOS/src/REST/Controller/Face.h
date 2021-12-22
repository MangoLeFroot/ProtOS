#pragma once

#include "PCH.h"

#include "REST/DTO/Face.h"
#include "REST/DTO/Status.h"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

namespace ProtOS {
    class FaceController : public oatpp::web::server::api::ApiController {
    public:
        /**
         * Constructor with object mapper.
         * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
         */
        FaceController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
                : oatpp::web::server::api::ApiController(objectMapper) {}

    public:

        ENDPOINT_INFO(face) {
            info->summary = "Get/Set the current face image.";

            info->addConsumes < Object < FaceDto >> ("application/json");

            info->addResponse < Object < FaceDto >> (Status::CODE_200, "application/json");
            info->addResponse < Object < StatusDto >> (Status::CODE_404, "application/json");
            info->addResponse < Object < StatusDto >> (Status::CODE_500, "application/json");

            info->pathParams["face"].description = "Face";
        }

        ENDPOINT("GET", "/face/", face) {
            auto dto = FaceDto::createShared();
            dto->name = "null";
            return createDtoResponse(Status::CODE_200, dto);
        }
    };
}

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen