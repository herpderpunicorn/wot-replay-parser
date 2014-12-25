#include <json/json.h>
#include "VehiclePosition.hpp"

namespace WotReplayParser {
namespace Payload {

VehiclePosition::VehiclePosition(std::vector<uint8_t>::iterator beginning, std::vector<uint8_t>::iterator end) {
    if (std::distance(beginning, end) < minimumSize()) {
        throw std::runtime_error("Data size smaller than minimum size for VehiclePosition");
    }
    playerId = *reinterpret_cast<uint32_t*>(&beginning[0]);
    beginning += sizeof(playerId);
    beginning += 8; // skip unknown 8 bytes
    const float x = *reinterpret_cast<float*>(&beginning[0]);
    beginning += sizeof(float);
    const float y = *reinterpret_cast<float*>(&beginning[0]);
    beginning += sizeof(float);
    const float z = *reinterpret_cast<float*>(&beginning[0]);
    beginning += sizeof(float);
    position      = std::make_tuple(x, y, z);
    beginning += 12; // skip unknown 12 bytes
    const float hx = *reinterpret_cast<float*>(&beginning[0]);
    beginning += sizeof(float);
    const float hy = *reinterpret_cast<float*>(&beginning[0]);
    beginning += sizeof(float);
    const float hz  = *reinterpret_cast<float*>(&beginning[0]);
    beginning += sizeof(float);
    hullOrientation = std::make_tuple(hx, hy, hz);
}

Json::Value VehiclePosition::toJson() {
    Json::Value root(Json::objectValue);
    root["playerId"]             = Json::Value(playerId);
    root["position"]             = Json::Value(Json::objectValue);
    root["position"]["x"]        = Json::Value(std::get<0>(position));
    root["position"]["y"]        = Json::Value(std::get<1>(position));
    root["position"]["z"]        = Json::Value(std::get<2>(position));
    root["hullOrientation"]      = Json::Value(Json::objectValue);
    root["hullOrientation"]["x"] = Json::Value(std::get<0>(hullOrientation));
    root["hullOrientation"]["y"] = Json::Value(std::get<1>(hullOrientation));
    root["hullOrientation"]["z"] = Json::Value(std::get<2>(hullOrientation));
    return root;
}

uint32_t VehiclePosition::getPlayerId() const {
    return playerId;
}

std::tuple<float, float, float> VehiclePosition::getPosition() const {
    return position;
}

std::tuple<float, float, float> VehiclePosition::getHullOrientation() const {
    return hullOrientation;
}
}
}
