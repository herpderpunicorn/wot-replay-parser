#pragma once

#include "Payload.hpp"

#include <vector>
#include <string>

namespace WotReplayParser {
namespace Payload {

class GameVersion : public Payload {
public:
    GameVersion() = delete;

    GameVersion(std::vector<uint8_t>::iterator beginning, std::vector<uint8_t>::iterator end);

    ~GameVersion() = default;

    virtual Json::Value toJson() override;

    std::string getVersionString();

protected:
    inline static size_t minimumSize() {
        return sizeof(length);
    }

private:
    uint32_t    length;
    std::string version;
};

} // Payload
} // WotReplayParser
