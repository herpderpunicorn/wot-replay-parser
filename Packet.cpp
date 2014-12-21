#include "Packet.hpp"
#include "Packets.hpp"

#include <json/json.h>

namespace WotReplayParser {

Packet::Packet(std::vector<uint8_t>::iterator beginning) {
    payloadSize = *reinterpret_cast<uint32_t*>(&beginning[0]);
    beginning += sizeof(payloadSize);
    type = *reinterpret_cast<PacketType*>(&beginning[0]);
    beginning += sizeof(type);
    clock = *reinterpret_cast<float*>(&beginning[0]);
    beginning += sizeof(clock);

    if (payloadSize > 0) {
        switch (type) {
        case BattleSetup:
            payload = std::make_unique<Payload::BattleSetup>(beginning);
            break;
        case GameStateUpdate:
        case VehiclePositionUpdate:
        case GameVersion:
        case MinimapClick:
        case EOS:
        default:
            break;
        }
    }
}

const size_t Packet::size() const {
    return sizeof(payloadSize) + sizeof(type) + sizeof(clock) + payloadSize;
}

const Packet::PacketType Packet::getType() const {
    return type;
}

Json::Value Packet::toJson() {
    Json::Value root(Json::objectValue);
    root["type"] = Json::Value(type);
    root["clock"] = Json::Value(clock);
    if (payload) {
        root["payload"] = payload->toJson();
    }
    return root;
}

}
