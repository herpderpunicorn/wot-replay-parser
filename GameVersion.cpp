
#include "GameVersion.hpp"

#include <json/json.h>

namespace WotReplayParser {
namespace Payload {

Json::Value GameVersion::toJson() {
    return Json::Value(Json::nullValue);
}

} // Payload
} // WotReplayParser
