#include <gtest/gtest.h>
#include <json/json.h>
#include "../DataBlock.hpp"

using namespace WotReplayParser;

TEST(DataBlock, Create) {
    std::vector<uint8_t> data;
    DataBlock dataBlock(data);
    ASSERT_EQ(dataBlock.getData(), data);
}
