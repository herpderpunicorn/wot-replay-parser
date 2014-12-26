#include "BattleSetup.hpp"

#include <json/json.h>

#include <cryptopp/base64.h>
#include <fstream>
#include <iostream>

namespace WotReplayParser {
namespace Payload {

BattleSetup::BattleSetup(std::vector<uint8_t>::iterator beginning, std::vector<uint8_t>::iterator end) {
    if (std::distance(beginning, end) < minimumSize()) {
        throw std::runtime_error("Data size smaller than minimum size for BattleSetup");
    }
    id = *reinterpret_cast<uint32_t*>(&beginning[0]);
    beginning += sizeof(id) + 6;

    uint8_t playerNameLength = beginning[0];
    beginning += sizeof(uint8_t);

    playerName = std::string(beginning, beginning + playerNameLength);
    beginning += playerNameLength;

    arenaUniqueID   = *reinterpret_cast<uint64_t*>(&beginning[0]);
    beginning += sizeof(arenaUniqueID);
    arenaCreateTime = arenaUniqueID & 0xffffffff;

    arenaTypeID = *reinterpret_cast<uint32_t*>(&beginning[0]);
    beginning += sizeof(arenaTypeID);
    gameplayID = arenaTypeID >> 16;
    mapId = arenaTypeID & 0x7fff;

    bonusType = beginning[0];
    beginning += sizeof(bonusType);
    guiType = beginning[0];
    beginning += sizeof(guiType);

    int pickleSize;
    if (beginning[0] == 0xff) {
        pickleSize = *reinterpret_cast<uint16_t*>(&beginning[1]);
        beginning += sizeof(uint32_t);
    } else {
        pickleSize = beginning[0];
        beginning += sizeof(uint8_t);
    }
    pickle = std::vector<uint8_t>(beginning, beginning + pickleSize);
}

Json::Value BattleSetup::toJson() {
    Json::Value root(Json::objectValue);
    root["id"] = Json::Value(id);
    root["player_name"] = Json::Value(playerName);
    root["arenaUniqueID"] = Json::Value((Json::UInt64)arenaUniqueID);
    root["arenaCreateTime"] = Json::Value((Json::UInt64)arenaCreateTime);
    root["arenaTypeID"] = Json::Value(arenaTypeID);
    root["gameplayID"] = Json::Value(gameplayID);
    root["mapId"] = Json::Value(mapId);
    root["bonusType"] = Json::Value(bonusType);
    root["guiType"] = Json::Value(guiType);
    std::string encoded;
    CryptoPP::StringSource(std::string(pickle.begin(), pickle.end()), true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(encoded)));
    root["pickle"] = Json::Value(encoded);
    return root;
}

} // Payload
} // WotReplayParser
