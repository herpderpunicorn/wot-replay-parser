#include "BattleResult.hpp"

#include "json\json.h"

namespace WotReplayParser {

void BattleResult::parse(Json::Value root) {
    personal.parse(root.get("personal", Json::nullValue));
    arenaUniqueID = root.get("arenaUniqueID", Json::nullValue).asUInt64();
}

}
