#include "BattleSetup.hpp"

#include <json/json.h>

#include "Common.hpp"

#include <cryptopp/base64.h>

namespace WotReplayParser {
namespace Payload {

BattleSetup::BattleSetup(std::vector<uint8_t>::iterator beginning) {
    id = swapEndian(*reinterpret_cast<uint32_t*>(&beginning[0]));
    beginning += sizeof(id) + 3; // 6 bytes are unknown
    playerNameLength = swapEndian(*reinterpret_cast<uint32_t*>(&beginning[0]));
    beginning += sizeof(playerNameLength);
    playerName = std::string(beginning, beginning + playerNameLength);
    beginning += playerNameLength + 11; // 11 bytes are unknown
    pickleSize = swapEndian(*reinterpret_cast<uint32_t*>(&beginning[0]));
    beginning += sizeof(pickleSize);
    pickle = std::vector<uint8_t>(beginning, beginning + pickleSize);
}

Json::Value BattleSetup::toJson() {
    Json::Value root(Json::objectValue);
    root["id"] = Json::Value(id);
    root["player_name"] = Json::Value(playerName);
    std::string encoded;
    CryptoPP::StringSource(std::string(pickle.begin(), pickle.end()), true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(encoded)));
    root["pickle"] = Json::Value(encoded);
    return root;
}

} // Payload
} // WotReplayParser
