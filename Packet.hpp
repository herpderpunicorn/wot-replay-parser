#pragma once

#include <cstdint>
#include <vector>
#include <array>
#include <memory>
#include <string>

#include <json/json-forwards.h>

#include "Payload.hpp"

namespace WotReplayParser {

class Packet {
public:
    enum PacketType : uint32_t {
        BattleSetup           = 0x00,
        GameStateUpdate       = 0x08,
        VehiclePositionUpdate = 0x0A,
        GameVersion           = 0x14,
        ChatMessage           = 0x1F,
        MinimapClick          = 0x21,
        EOS                   = 0xFFFFFFFF
    };

    Packet() = delete;

    Packet(std::vector<uint8_t>::iterator beginning);

    ~Packet() = default;

    /**
    * Returns the size of the packet in the event stream.
    */
    const size_t size() const;

    const PacketType getType() const;

    /**
    * Exports the Packet to a json object.
    */
    Json::Value toJson();

    template<class T>
    const T& getPayload() const;

private:
    uint32_t                          payloadSize;
    PacketType                        type;
    float                             clock;
    std::unique_ptr<Payload::Payload> payload;
};

template<class T>
const T& Packet::getPayload() const {
    if (typeid(T) != typeid(*payload)) {
        throw std::runtime_error("Payload is not of the requested type");
    }
    return (T&) *payload;
}

}
