#pragma once

#include "Payload.hpp"

#include <string>
#include <vector>

namespace WotReplayParser {
namespace Payload {

/**
* uint   id         (0, 4)
* ...    unknown    (4, 6)
* byte   nameLen    (10, 1)
* string playerName (14, nameLen)
* ...    unknown    (14+nameLen, 11)
* uint   pickleSize (25+nameLen, 4)
* ...    pickle     (29+nameLen, pickleSize)
*/

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
    uint32_t playerNameLength;
    /**
    * The player name
    */
    std::string playerName;
    /**
    * Size of the pickle
    */
    uint32_t pickleSize;
    /**
    * The raw pickle
    */
    std::vector<uint8_t> pickle;
};

} // Payload
} // WotReplayParser
