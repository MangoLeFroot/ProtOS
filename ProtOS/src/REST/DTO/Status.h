#pragma once

#include "PCH.h"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace ProtOS {
    class StatusDto : public oatpp::DTO {

        DTO_INIT(StatusDto, DTO)

        DTO_FIELD(String, status);
        DTO_FIELD(Int32, code);
        DTO_FIELD(String, message);

        DTO_FIELD_INFO(status) { info->description = "Short status text"; }
        DTO_FIELD_INFO(code) { info->description = "Status code"; }
        DTO_FIELD_INFO(message) { info->description = "Verbose message"; }
    };
}

#include OATPP_CODEGEN_END(DTO)