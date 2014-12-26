#include "Vehicle.hpp"

#include <json/json.h>

namespace WotReplayParser {

void Vehicle::parse(Json::Value root) {
    vehicleType  = root.get("vehicleType", Json::nullValue).asString();
    isAlive      = root.get("isAlive", Json::nullValue).asBool();
    name         = root.get("name", Json::nullValue).asString();
    clanAbbrev   = root.get("clanAbbrev", Json::nullValue).asString();
    team         = root.get("team", Json::nullValue).asUInt();
    isTeamKiller = root.get("isTeamKiller", Json::nullValue).asBool();
}

}
