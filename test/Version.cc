#include <gtest/gtest.h>

#include "../Version.hpp"

using namespace WotReplayParser;

TEST(Version, Equality) {
    Version v1234(1, 2, 3, 4);
    Version v4321(4, 3, 2, 1);
    EXPECT_NE(v1234, v4321);
    EXPECT_LT(v1234, v4321);
    EXPECT_GT(v4321, v1234);

    // Build number should not cause inequality
    Version v1235(1, 2, 3, 5);
    EXPECT_EQ(v1234, v1235);
}

TEST(Version, FromString) {
    EXPECT_EQ(Version::getVersionFromString("1.2.3 #4"),   Version::getVersionFromString("1, 2, 3, 4"));
    EXPECT_NE(Version::getVersionFromString("1.2.3 #4"),   Version::getVersionFromString("4, 3, 2, 1"));
    EXPECT_LT(Version::getVersionFromString("1.2.3 #4"),   Version::getVersionFromString("4, 3, 2, 1"));
    EXPECT_GT(Version::getVersionFromString("4, 3, 2, 1"), Version::getVersionFromString("1.2.3 #4"));
}
