#include "Version.hpp"

#include <regex>

namespace WotReplayParser {

Version::Version(int major, int minor, int maintenance, int build) {
    mMajor = major;
    mMinor = minor;
    mMaintenance = maintenance;
    mBuild = build;
}

void Version::setVersion(const std::string& version) {
    Version v = getVersionFromString(version);
    mMajor = v.mMajor;
    mMinor = v.mMinor;
    mMaintenance = v.mMaintenance;
    mBuild = v.mBuild;
}

void Version::setVersion(int major, int minor, int maintenance, int build) {
    mMajor = major;
    mMinor = minor;
    mMaintenance = maintenance;
    mBuild = build;
}

int Version::major() {
    return mMajor;
}

int Version::minor() {
    return mMinor;
}

int Version::maintenance() {
    return mMaintenance;
}

int Version::build() {
    return mBuild;
}

Version Version::getVersionFromString(const std::string& version) {
    std::smatch sm;
    bool res = std::regex_match(version, sm, std::regex { R"(.*?(\d+)(?:\.|,\s)(\d+)(?:\.|,\s)(\d+)(?:\s#|,\s)(\d+).*?)" });
    if (!res || sm.size() != 5) {
        throw new std::invalid_argument("Unable to get version from string");
    }
    return Version(std::stoi(sm[1]), std::stoi(sm[2]), std::stoi(sm[3]), std::stoi(sm[4]));
}

}
