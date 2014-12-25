#include <gtest/gtest.h>
#include <json/json.h>
#include <fstream>
#include "../BattleSetup.hpp"

using namespace WotReplayParser::Payload;

TEST(BattleSetup, Create) {
    std::vector<uint8_t> data{
            0x0,0x0,0x0,0x0,    // id
            0x0,0x0,0x0,        // unknown
            0x0,0x0,0x0,0x4,    // name length
            't', 'e', 's', 't', // name
            0x0,0x0,0x0,0x0,    // unknown
            0x0,0x0,0x0,0x0,    // unknown
            0x0,0x0,0x0,        // unknown
            0x0,0x0,0x0,0x0,    // pickle size
            0x0                 // pickle
    };
    ASSERT_NO_THROW(BattleSetup(data.begin(), data.end()));

    std::ifstream file("data/battle_setup.dat", std::ios::binary);
    ASSERT_TRUE(file.is_open()) << "Unable to open 'data/battle_setup.dat'";
    data = std::vector<uint8_t>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    ASSERT_NO_THROW(BattleSetup(data.begin(), data.end()));

    data.clear();
    ASSERT_ANY_THROW(BattleSetup(data.begin(), data.end()));
}
