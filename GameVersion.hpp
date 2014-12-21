#pragma once

#include "Payload.hpp"

namespace WotReplayParser {
namespace Payload {

class GameVersion : public Payload {
public:
    GameVersion() = default;

    ~GameVersion() = default;

    virtual Json::Value toJson() override;

private:
    uint32_t length;
};

} // Payload
} // WotReplayParser
