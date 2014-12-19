#pragma once

#include <cstdint>
#include <string>
#include <map>

#include "BattleResult.hpp"
#include "Vehicle.hpp"

namespace WotReplayParser {

class MatchData {
public:
    struct FragInfo {
        uint32_t frags;
    };
    MatchData() = default;
    ~MatchData() = default;

    void parse(std::vector<uint8_t> data);
    void parse(std::string json);

private:
    BattleResult battleResult;
    std::map<std::string, Vehicle> vehicles;
    std::map<std::string, FragInfo> frags;
};

}
