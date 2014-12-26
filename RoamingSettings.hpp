#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include <json/json-forwards.h>

namespace WotReplayParser {

/**
* Actual meaning of values is unknown.
* Variable names are pure guesses.
*/
class RoamingSettings {
public:
    struct ServerInfo {
        uint32_t    serverRegion;
        uint32_t    unkownVal1;
        uint64_t    unkownVal2;
        std::string regionCode;
    };

    RoamingSettings() = default;

    ~RoamingSettings() = default;

    void parse(Json::Value root);

private:
    uint32_t                serverRegion;
    uint32_t                server;
    std::vector<ServerInfo> servers;
};

}
