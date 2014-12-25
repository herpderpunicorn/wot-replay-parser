#include <gtest/gtest.h>
#include <fstream>
#include "../GameVersion.hpp"

using namespace WotReplayParser::Payload;

TEST(GameVersion, Create) {
    std::ifstream file("data/game_version.dat", std::ios::binary);
    ASSERT_TRUE(file.is_open()) << "Unable to open 'data/game_version.dat'";
    std::vector<uint8_t> data = std::vector<uint8_t>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    ASSERT_NO_THROW(GameVersion(data.begin(), data.end()));
}