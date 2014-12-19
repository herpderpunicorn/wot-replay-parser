#pragma once

#include <cstdint>
#include <vector>
#include <iterator>

namespace WotReplayParser {

/**
 * A block of raw replay data.
 * It contains either json info about the game or the compressed and encrypted replay data.
 */
class DataBlock {
public:
    DataBlock() = delete;
    DataBlock(std::vector<uint8_t> data);
    DataBlock(const std::vector<uint8_t>::iterator& begin, const std::vector<uint8_t>::iterator& end, uint32_t size);
    DataBlock(const std::vector<uint8_t>::iterator& begin, const std::vector<uint8_t>::iterator& end);
    ~DataBlock() = default;

    const std::vector<uint8_t>& getData();

private:
    std::vector<uint8_t> mData;
};

}
