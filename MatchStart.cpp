#include "MatchStart.hpp"

#include "json/json.h"

namespace WotReplayParser {

bool MatchStart::parse(std::vector<uint8_t> data) {
    std::string json(data.begin(), data.end());
    return parse(json);
}

bool MatchStart::parse(std::string json) {
    Json::Reader reader;
    Json::Value root;
    bool parsed = reader.parse(json, root, false);
    if (!parsed) {
        throw std::invalid_argument("Unable to parse json");
    }
    romingSettings.parse(root.get("roamingSettings", Json::nullValue));
    clientVersionFromXml = root.get("clientVersionFromXml", Json::nullValue).asString();
    clientVersionFromExe = root.get("clientVersionFromExe", Json::nullValue).asString();
    mapDisplayName = root.get("mapDisplayName", Json::nullValue).asString();
    gameplayID = root.get("gameplayID", Json::nullValue).asString();
    regionCode = root.get("regionCode", Json::nullValue).asString();
    playerID = root.get("playerID", Json::nullValue).asUInt();
    serverName = root.get("serverName", Json::nullValue).asString();
    Json::Value vehiclesRoot = root.get("vehicles", Json::nullValue);
    if (vehiclesRoot.size() > 0) {
        for (auto it = vehiclesRoot.begin(); it != vehiclesRoot.end(); it++) {
            std::string key(it.memberName());
            Json::Value vehicleRoot = vehiclesRoot.get(key, Json::nullValue);
            Vehicle value;
            value.parse(vehicleRoot);
            vehicles.insert(std::make_pair(key, value));
        }
    }
    dateTime = root.get("dateTime", Json::nullValue).asString();
    mapName = root.get("mapName", Json::nullValue).asString();
    playerName = root.get("playerName", Json::nullValue).asString();
    battleType = root.get("battleType", Json::nullValue).asUInt();
    playerVehicle = root.get("playerVehicle", Json::nullValue).asString();
    return true;
}

}
