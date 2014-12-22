#pragma once

#include "Payload.hpp"

#include <string>
#include <vector>

namespace WotReplayParser {
namespace Payload {

/**
* uint   id         (0, 4)
* ...    unkown     (4, 6)
* byte   nameLen    (10, 1)
* string playerName (14, nameLen)
* ...    unkown     (14+nameLen, 11)
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
    */
    BattleSetup(std::vector<uint8_t>::iterator beginning);

    ~BattleSetup() = default;

    /**
    * Creates a Json::Value from the payload.
    * @return The payload as a Json::Value
    */
    virtual Json::Value toJson() override;

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
