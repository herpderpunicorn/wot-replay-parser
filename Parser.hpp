#pragma once

#include <istream>
#include <cstdint>
#include <vector>
#include <utility>

#include "DataBlock.hpp"

namespace WotReplayParser {

class Parser {
public:
    Parser() = default;
    ~Parser() = default;

    /**
     * Parses a stream.
     * @param is The stream contaning the replay.
     */
    void parse(std::istream& is);

    std::vector<std::string> extractJson(std::istream& is);
protected:
    bool isLegacy(const std::vector<uint8_t>& buffer) const;

    std::vector<DataBlock> getDataBlocks(std::vector<uint8_t> buffer);

    /**
     * Get the block count from the buffer.
     * @param buffer Must be at least eight bytes.
     */
    uint32_t getDataBlockCount(std::vector<uint8_t> buffer);
private:
};

}
