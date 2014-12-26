#include <gtest/gtest.h>
#include <fstream>
#include "../UnPickle.hpp"


using namespace WotReplayParser;

TEST(UnPickle, Create) {
    std::ifstream file("data/battle_setup_pickle.dat", std::ios::binary);
    ASSERT_TRUE(file.is_open()) << "Unable to open 'data/battle_setup_pickle.dat'";
    std::vector<uint8_t> data = std::vector<uint8_t>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    ASSERT_NO_THROW(UnPickle(data.begin(), data.end()));
}


TEST(UnPickle, toJsonReturnsObject) {
    std::ifstream file("data/battle_setup_pickle.dat", std::ios::binary);
    ASSERT_TRUE(file.is_open()) << "Unable to open 'data/battle_setup_pickle.dat'";
    std::vector<uint8_t> data = std::vector<uint8_t>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    auto json = UnPickle(data.begin(), data.end()).toJson();
    ASSERT_TRUE(json.isObject());
}

TEST(UnPickle, toJsonReturnsJsonObjectWithCorrectContents) {
    std::ifstream file("data/battle_setup_pickle.dat", std::ios::binary);
    ASSERT_TRUE(file.is_open()) << "Unable to open 'data/battle_setup_pickle.dat'";
    std::vector<uint8_t> data = std::vector<uint8_t>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    auto json = UnPickle(data.begin(), data.end()).toJson();
    Json::Value expected;
    ASSERT_TRUE(Json::Reader().parse(R"({"battleLevel": 11})", expected, true));
    ASSERT_EQ(expected, json);

}
