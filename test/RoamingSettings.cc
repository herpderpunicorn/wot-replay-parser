#include <gtest/gtest.h>
#include <json/json.h>
#include <fstream>
#include "../RoamingSettings.hpp"

using namespace WotReplayParser;

TEST(RomingSettingsTests, ParseJson) {
    std::ifstream is("data/roaming_settings.json", std::ios::binary);
    RoamingSettings roamingSettings;
    Json::Value root;
    Json::Reader reader;
    ASSERT_TRUE(reader.parse(is, root, false));
    roamingSettings.parse(root);
}
