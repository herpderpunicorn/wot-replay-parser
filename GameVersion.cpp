#include "GameVersion.hpp"

#include <json/json.h>

namespace WotReplayParser {
namespace Payload {

GameVersion::GameVersion(std::vector<uint8_t>::iterator beginning, std::vector<uint8_t>::iterator end) {
    if (std::distance(beginning, end) < minimumSize()) {
        throw std::runtime_error("Data size too small to contain GamveVersion");
    }
    length  = *reinterpret_cast<uint32_t*>(&beginning[0]);
    beginning += sizeof(length);
    version = std::string(beginning, beginning + length);
    beginning += length;
}

Json::Value GameVersion::toJson() {
    return Json::Value(Json::nullValue);
}

std::string GameVersion::getVersionString() {
    return version;
}

} // Payload
} // WotReplayParser
