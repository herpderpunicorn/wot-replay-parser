
#include "GameState.hpp"

#include <json/json.h>

namespace WotReplayParser {
namespace Payload {

Json::Value GameState::toJson() {
    return Json::Value(Json::nullValue);
}

} // Payload
} // WotReplayParser
