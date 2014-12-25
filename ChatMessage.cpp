#include <json/json.h>
#include "ChatMessage.hpp"

namespace WotReplayParser {
namespace Payload {

ChatMessage::ChatMessage(std::vector<uint8_t>::iterator beginning, std::vector<uint8_t>::iterator end) {
    if (std::distance(beginning, end) < minimumSize()) {
        throw std::runtime_error("Data size smaller than minimum size for ChatMessage");
    }
    uint32_t length = *reinterpret_cast<uint32_t*>(&beginning[0]);
    beginning += sizeof(length);
    message = std::string(beginning, beginning + length);
}

Json::Value ChatMessage::toJson() {
    Json::Value root(Json::objectValue);
    root["message"] = Json::Value(message);
    return root;
}

std::string ChatMessage::getMessage() const {
    return message;
}

}
}