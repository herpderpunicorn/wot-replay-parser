#pragma once

#include <cstdint>
#include <string>
#include <map>

#include "json/json-forwards.h"
#include "Personal.hpp"

namespace WotReplayParser {

/** \breif The battle result
* The battle result parsed from the battle result json.
*/
class BattleResult {
public:
    BattleResult() = default;

    ~BattleResult() = default;

    void parse(Json::Value root);

private:
    Personal personal;
    std::map<std::string, int> players;
    std::map<std::string, int> vehicles;
    // common
    uint64_t arenaUniqueID;
};

}
