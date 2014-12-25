#include <gtest/gtest.h>
#include <fstream>
#include "../ChatMessage.hpp"

using namespace WotReplayParser::Payload;

TEST(ChatMessage, Create) {
    std::ifstream file("data/chat_message.dat", std::ios::binary);
    ASSERT_TRUE(file.is_open()) << "Unable to open 'data/chat_message.dat'";
    std::vector<uint8_t> data = std::vector<uint8_t>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    ASSERT_NO_THROW(ChatMessage(data.begin(), data.end()));
}
