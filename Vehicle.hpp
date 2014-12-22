#pragma once

#include <string>
#include <cstdint>

#include "json/json-forwards.h"

namespace WotReplayParser {

class Vehicle {
public:
    Vehicle() = default;

    ~Vehicle() = default;

    void parse(Json::Value root);

private:
    std::string vehicleType;
    bool isAlive;
    std::string name;
    std::string clanAbbrev;
    uint32_t team;
    // Events, json object, unkown structure
    bool isTeamKiller;
};

}
