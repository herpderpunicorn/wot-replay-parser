#pragma once

#include <istream>
#include <cstdint>
#include <vector>
#include <utility>
#include <functional>

#include "DataBlock.hpp"

namespace WotReplayParser {

class Packet;

class Parser {
public:
    Parser() = default;

    ~Parser() = default;

    /**
     * Sets the packet callback which is called for every packet in event stream
    * @param callback Function accepting a Packet
     */
    void setPacketCallback(const std::function<void(const Packet&)>& callback);

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
    std::function<void(const Packet&)> mPacketCallback;
};

}
