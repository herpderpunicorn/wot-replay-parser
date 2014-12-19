#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <map>

#include "RoamingSettings.hpp"
#include "Vehicle.hpp"

namespace WotReplayParser {

class MatchStart {
public:
    MatchStart() = default;
    ~MatchStart() = default;

    bool parse(std::vector<uint8_t> data);
    bool parse(std::string json);

    int getVersion();

private:
    RoamingSettings romingSettings;
    std::string clientVersionFromXml;
    std::string clientVersionFromExe;
    std::string mapDisplayName;
    std::string gameplayID;
    std::string regionCode;
    uint32_t playerID;
    std::string serverName;
    std::map<std::string, Vehicle> vehicles;
    std::string dateTime;
    std::string mapName;
    std::string playerName;
    uint32_t battleType;
    std::string playerVehicle;
};

}
