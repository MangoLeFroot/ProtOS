#pragma once

// IO
#include <stdio.h>
#include <fstream>
#include <map>
#include <memory>

// Matrix library
#include "led-matrix.h"
#include "graphics.h"

// JSON
#include "nlohmann/json.hpp"

// Imaeg processing
#include <Magick++.h>

// RESTful API
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/Types.hpp"
#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"

// RESTful Swagger API
#include "oatpp-swagger/Controller.hpp"
#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"
