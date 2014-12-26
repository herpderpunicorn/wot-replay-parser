#pragma once

#include "Payload.hpp"

#include <string>
#include <vector>

namespace WotReplayParser {
namespace Payload {

class ChatMessage : public Payload {
public:
    ChatMessage() = delete;

    ChatMessage(std::vector<uint8_t>::iterator beginning, std::vector<uint8_t>::iterator end);

    ~ChatMessage() = default;

    virtual Json::Value toJson() override;

    std::string getMessage() const;

private:
    /**
    * @return The minimum size a Packet of this type can be
    */
    inline static size_t minimumSize() {
        // Min size is a message length of zero.
        return sizeof(uint32_t);
    }

    std::string message;
};

}
}