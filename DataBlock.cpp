#include "DataBlock.hpp"

namespace WotReplayParser {

DataBlock::DataBlock(std::vector<uint8_t> data) {
    mData = data;
}

DataBlock::DataBlock(const std::vector<uint8_t>::iterator& begin, const std::vector<uint8_t>::iterator& end, uint32_t size) {
    mData.resize(size);
    std::copy(begin, end, mData.begin());
}

DataBlock::DataBlock(const std::vector<uint8_t>::iterator& begin, const std::vector<uint8_t>::iterator& end) {
    size_t size = std::distance(begin, end);
    mData.resize(size);
    std::copy(begin, end, mData.begin());
}

const std::vector<uint8_t>& DataBlock::getData() {
    return mData;
}

}
