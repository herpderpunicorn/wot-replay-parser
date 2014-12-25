#include <gtest/gtest.h>
#include <json/json.h>
#include <fstream>
#include "../Parser.hpp"
#include "../Packet.hpp"

using namespace WotReplayParser;

class ParserTests : public ::testing::Test{
protected:
    Parser parser;
};

TEST_F(ParserTests, Parse) {
    std::ifstream is("data/test_replay.wotreplay", std::ios::binary);
    parser.parse(is);
}

TEST_F(ParserTests, packetCallbackIsCalled) {
    bool called = false;
    parser.setPacketCallback([&called](const Packet& packet) {
        called = true;
    });
    std::ifstream is("data/test_replay.wotreplay", std::ios::binary);
    parser.parse(is);
    ASSERT_TRUE(called);
}

TEST_F(ParserTests, eosPacketIsReceivedInCallback) {
    bool eosReceived = false;
    parser.setPacketCallback([&eosReceived](const Packet& packet) {
        ASSERT_FALSE(eosReceived);
        if (packet.getType() == Packet::EOS)
            eosReceived = true;
    });
    std::ifstream is("data/test_replay.wotreplay", std::ios::binary);
    parser.parse(is);
    ASSERT_TRUE(eosReceived);
}

