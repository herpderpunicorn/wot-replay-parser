#pragma once

#include <string>
#include <array>

namespace WotReplayParser {

class Version {
public:
    Version() = default;

    Version(int major, int minor, int maintenance, int build);

    ~Version() = default;

    bool operator<(const Version& rhs) {
        return mMajor < rhs.mMajor || mMinor < rhs.mMinor || mMaintenance < rhs.mMaintenance;
    }

    friend bool operator<(const Version& lhs, const Version& rhs) {
        return lhs.mMajor < rhs.mMajor || lhs.mMinor < rhs.mMinor || lhs.mMaintenance < rhs.mMaintenance;
    }

    bool operator>(const Version& rhs) {
        return mMajor > rhs.mMajor || mMinor > rhs.mMinor || mMaintenance > rhs.mMaintenance;
    }

    friend bool operator>(const Version& lhs, const Version& rhs) {
        return lhs.mMajor > rhs.mMajor || lhs.mMinor > rhs.mMinor || lhs.mMaintenance > rhs.mMaintenance;
    }

    bool operator==(const Version& rhs) {
        return mMajor == rhs.mMajor && mMinor == rhs.mMinor && mMaintenance == rhs.mMaintenance;
    }

    friend bool operator==(const Version& lhs, const Version& rhs) {
        return lhs.mMajor == rhs.mMajor && lhs.mMinor == rhs.mMinor && lhs.mMaintenance == rhs.mMaintenance;
    }

    void setVersion(const std::string& version);

    void setVersion(int major, int minor, int maintenance, int build);

    int major();

    int minor();

    int maintenance();

    int build();

    /**
    * Get version from a string in one of the following formats:
    *   0, 9, 1, 0
    *   0.9.1 #719
    */
    static Version getVersionFromString(const std::string& version);

private:
    int mMajor;
    int mMinor;
    int mMaintenance;
    int mBuild;
};

static const Version v0_9_0_0(0, 9, 0, 0);
static const Version v0_9_1_0(0, 9, 1, 0);
static const Version v0_9_2_0(0, 9, 2, 0);
static const Version v0_9_3_0(0, 9, 3, 0);
static const Version v0_9_4_0(0, 9, 4, 0);
}
