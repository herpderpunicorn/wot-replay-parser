#include <gtest/gtest.h>
#include <json/json.h>
#include <fstream>
#include "../Parser.hpp"

using namespace WotReplayParser;

TEST(Parser, Parse) {
    Parser parser;
    std::ifstream is("data/test_replay.wotreplay", std::ios::binary);
    parser.parse(is);
}
