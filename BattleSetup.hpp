#pragma once

#include "Payload.hpp"

#include <string>
#include <vector>

namespace WotReplayParser {
namespace Payload {

/** \brief Battle setup payload
*
*/
class BattleSetup : public Payload {
public:
    BattleSetup() = delete;

    /**
    * @param beginning The start of the payload
    * @param end The end of the payload
    */
    BattleSetup(std::vector<uint8_t>::iterator beginning, std::vector<uint8_t>::iterator end);

    ~BattleSetup() = default;

    /**
    * Creates a Json::Value from the payload.
    * @return The payload as a Json::Value
    */
    virtual Json::Value toJson() override;

protected:
    /**
    * @return The minimum size a Packet of this type can be
    */
    inline static size_t minimumSize() {
        return sizeof(id) + sizeof(playerNameLength) + sizeof(pickleSize) + 14;
    }

private:
    /**
    * Id of the battle
    */
    uint32_t id;
    /**
    * Length of the player name string
    */
    uint8_t playerNameLength;
    /**
    * The player name
    */
    std::string playerName;

    uint64_t arenaUniqueID;
    uint64_t arenaCreateTime;

    uint32_t arenaTypeID;
    uint32_t gameplayID;
    uint32_t mapId;

    uint8_t bonusType;

    uint8_t guiType;

    /**
    * Size of the pickle
    */
    uint16_t pickleSize;
    /**
    * The raw pickle
    */
    std::vector<uint8_t> pickle;
};

} // Payload
} // WotReplayParser
