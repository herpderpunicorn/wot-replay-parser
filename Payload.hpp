#pragma once

#include <cstdint> // Most childs will use this
#include <json/json-forwards.h>

namespace WotReplayParser {
namespace Payload {

/** \brief Base class for payloads
* Abstract base class for Packet payloads.
*/
class Payload {
public:
    Payload() = default;

    virtual ~Payload() = default;

    /**
    * Creates a Json::Value from the payload.
    * @return The payload as a Json::Value
    */
    virtual Json::Value toJson() = 0;
};

} // Payload
} // WotReplayParser
