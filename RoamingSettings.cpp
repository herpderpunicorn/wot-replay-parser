#include "RoamingSettings.hpp"

#include <json/json.h>

namespace WotReplayParser {

void RoamingSettings::parse(Json::Value root) {
    if (root.isArray() && root.size() >= 3) {
        serverRegion = root[0].asUInt();
        server = root[1].asUInt();

        if (root[2].isArray()) {
            for (auto it = root[2].begin(); it != root[2].end(); it++) {
                if (root[2][it.index()].isArray() && root[2][it.index()].size() == 4) {
                    ServerInfo info;
                    info.serverRegion = root[2][it.index()][0].asUInt();
                    info.unkownVal1 = root[2][it.index()][1].asUInt();
                    info.unkownVal2 = root[2][it.index()][2].asUInt64();
                    info.regionCode = root[2][it.index()][3].asString();
                    servers.push_back(info);
                }
            }
        }
    }
}

}
