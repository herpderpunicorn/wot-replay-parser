#pragma once

#include <tuple>
#include <vector>
#include "Payload.hpp"

namespace WotReplayParser {
namespace Payload {

class VehiclePosition : public Payload {
public:
    VehiclePosition() = default;

    VehiclePosition(std::vector<uint8_t>::iterator beginning, std::vector<uint8_t>::iterator end);

    ~VehiclePosition() = default;

    virtual Json::Value toJson() override;

    uint32_t getPlayerId() const;

    std::tuple<float, float, float> getPosition() const;

    std::tuple<float, float, float> getHullOrientation() const;

private:
    uint32_t minimumSize() {
        return sizeof(uint32_t) + 8 + sizeof(float) * 3 + sizeof(float) * 3 + 12 + 1;
    }

    uint32_t                        playerId;
    std::tuple<float, float, float> position;
    std::tuple<float, float, float> hullOrientation;
};
} // Payload
} // WotReplayParser
