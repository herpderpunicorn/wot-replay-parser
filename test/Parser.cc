#include <gtest/gtest.h>
#include <json/json.h>
#include <fstream>
#include "../Parser.hpp"
#include "../Packet.hpp"
#include "../BattleSetup.hpp"

using namespace WotReplayParser;

class ParserTests : public ::testing::Test{
protected:
    Parser parser;
};

TEST_F(ParserTests, ParseV094) {
    std::ifstream is("data/v0.9.4_replay.wotreplay", std::ios::binary);
    parser.parse(is);
}

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

TEST_F(ParserTests, getPayload) {
    bool called = false;
    parser.setPacketCallback([&called](const Packet& packet) {
        if (packet.getType() == Packet::BattleSetup) {
            ASSERT_NO_THROW(packet.getPayload<Payload::BattleSetup>());
            called = true;
        }
    });
    std::ifstream is("data/test_replay.wotreplay", std::ios::binary);
    parser.parse(is);
    ASSERT_TRUE(called) << "Did not find a BattleSetup package";
}

TEST_F(ParserTests, getPayloadThrow) {
    bool thrown = false;
    parser.setPacketCallback([&thrown](const Packet& packet) {
        if (packet.getType() != Packet::BattleSetup) {
            ASSERT_ANY_THROW(packet.getPayload<Payload::BattleSetup>());
            thrown = true;
        }
    });
    std::ifstream is("data/test_replay.wotreplay", std::ios::binary);
    parser.parse(is);
    ASSERT_TRUE(thrown) << "Found only BattleSetup packages";
}
