#include "MatchData.hpp"

#include "json/json.h"

namespace WotReplayParser {

void MatchData::parse(std::vector<uint8_t> data) {
    std::string json(data.begin(), data.end());
    return parse(json);
}

void MatchData::parse(std::string json) {
    Json::Reader reader;
    Json::Value root;
    bool parsed = reader.parse(json, root, false);
    if (!parsed) {
        throw new std::invalid_argument("Unable to parse json");
    }
    if (root.isArray() && root.size() == 3) {
        battleResult.parse(root[0]);

        if (root[1].size() > 0) {
            for (auto it = root[1].begin(); it != root[1].end(); it++) {
                std::string key(it.memberName());
                Json::Value vehicleRoot = root[1].get(key, Json::nullValue);
                Vehicle value;
                value.parse(vehicleRoot);
                vehicles.insert(std::make_pair(key, value));
            }
        }
        if (root[2].size() > 0) {
            for (auto it = root[2].begin(); it != root[2].end(); it++) {
                std::string key(it.memberName());
                Json::Value fragInfoRoot = root[2].get(key, Json::nullValue);
                FragInfo value;
                value.frags = fragInfoRoot.get("frags", Json::nullValue).asUInt();
                frags.insert(std::make_pair(key, value));
            }
        }
    } else {
        throw new std::invalid_argument("Unable to parse match data, root was invalid");
    }
}

}
