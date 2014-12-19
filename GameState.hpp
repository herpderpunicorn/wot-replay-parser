#pragma once

#include "Payload.hpp"

namespace WotReplayParser {
namespace Payload {

class GameState : public Payload {
public:
    enum UpdateType : uint8_t {
        VehicleList = 0x01,
        VehicleConnected = 0x02,
        Period = 0x03,
        VehicleStatistics = 0x04,
        VehicleStatistic = 0x05,
        VehicleKilled = 0x06,
        AvatarReady = 0x07,
        BaseCupture = 0x08,
        BaseCuptured = 0x09,
        TeamKiller = 0x0A,
        VehickeUpdate = 0x0B,
    };

    GameState() = default;
    ~GameState() = default;

    virtual Json::Value toJson() override;

private:
    // TODO: add data
};

} // Payload
} // WotReplayParser
