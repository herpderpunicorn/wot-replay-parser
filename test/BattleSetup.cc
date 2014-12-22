#include <gtest/gtest.h>
#include <json/json.h>
#include "../BattleSetup.hpp"

using namespace WotReplayParser::Payload;

TEST(BattleSetup, Create) {
    std::vector<uint8_t> data{
            0x0,0x0,0x0,0x0,    // id
            0x0,0x0,0x0,        // unkown
            0x0,0x0,0x0,0x4,    // name length
            't', 'e', 's', 't', // name
            0x0,0x0,0x0,0x0,    // unkown
            0x0,0x0,0x0,0x0,    // unkown
            0x0,0x0,0x0,        // unkown
            0x0,0x0,0x0,0x0,    // pickle size
            0x0                 // pickle
    };
    ASSERT_NO_THROW(BattleSetup(data.begin()));

}