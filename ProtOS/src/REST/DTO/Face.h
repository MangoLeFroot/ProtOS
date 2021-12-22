#pragma once

#include "PCH.h"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace ProtOS {
    class FaceDto : public oatpp::DTO {

        DTO_INIT(FaceDto, DTO)

        DTO_FIELD(String, name, "name");
    };
}

#include OATPP_CODEGEN_END(DTO)