#include <gtest/gtest.h>
#include <fstream>
#include "../VehiclePosition.hpp"

using namespace WotReplayParser::Payload;

TEST(VehiclePosition, Create) {
    std::ifstream file("data/vehicle_position.dat", std::ios::binary);
    ASSERT_TRUE(file.is_open()) << "Unable to open 'data/vehicle_position.dat'";
    std::vector<uint8_t> data = std::vector<uint8_t>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    ASSERT_NO_THROW(VehiclePosition(data.begin(), data.end()));
}
