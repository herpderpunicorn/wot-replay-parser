// Parser.cpp

#include "Parser.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include "MatchStart.hpp"
#include "MatchData.hpp"
#include "Packet.hpp"

// For decrypt of event stream
#include <cryptopp/blowfish.h>
// For event stream inflation
#include <zlib/zlib.h>

#include <json/json.h>

namespace WotReplayParser {

void Parser::parse(std::istream& is) {
    std::vector<uint8_t> buffer = std::vector<uint8_t>(std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>());
    const uint32_t magicNumber = (buffer[0] << 0) | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24);
    if (magicNumber != 0x11343212) {
        throw new std::runtime_error("Unexpected magic number in header");
    }

    // Vector of data ranges
    std::vector<DataBlock> dataBlocks(getDataBlocks(buffer));

    if (dataBlocks.size() < 2) {
        throw new std::runtime_error("Unexpected number of blocks");
    }
    MatchStart matchStart;
    matchStart.parse(dataBlocks[0].getData());

    MatchData matchData;
    if (dataBlocks.size() >= 3) {
        matchData.parse(dataBlocks[1].getData());
    }
    static const uint8_t key[16] = { // Blowfish key
            0xDE, 0x72, 0xBE, 0xA0,
            0xDE, 0x04, 0xBE, 0xB1,
            0xDE, 0xFE, 0xBE, 0xEF,
            0xDE, 0xAD, 0xBE, 0xEF
    };

    std::vector<uint8_t> replayData(dataBlocks.back().getData().begin(), dataBlocks.back().getData().end()); // Compressed and encrypted event stream

    // Decrypt replay data
    CryptoPP::BlowfishDecryption decryptor;
    decryptor.SetKey(key, 16);

    const size_t blockSize = 8;
    uint8_t previousBlock[blockSize] = {0};
    uint8_t decryptedBlock[blockSize] = {0};
    uint8_t encryptedBlock[blockSize] = {0};

    for (size_t i = 0; i < replayData.size(); i += blockSize) {
        std::copy(&replayData[i], (&replayData[i]) + blockSize, encryptedBlock);
        decryptor.ProcessAndXorBlock(encryptedBlock, previousBlock, decryptedBlock);
        std::copy_n(decryptedBlock, blockSize, previousBlock);
        std::copy_n(decryptedBlock, blockSize, &replayData[i]);
    }

    std::vector<uint8_t> eventStream; // Raw event stream

    // Decompress replay data
    z_stream stream = {
            reinterpret_cast<uint8_t*>(&(replayData[0])),
            static_cast<uInt>(replayData.size())
    };
    int ret = inflateInit(&stream);
    if (ret != Z_OK) {
        throw std::runtime_error("Unable to init zlib inflate");
    }

    const int chunk = 1024 * 1024;
    std::unique_ptr<uint8_t[]> out(new uint8_t[chunk]);

    do {
        stream.avail_out = chunk;
        stream.next_out = out.get();
        ret = inflate(&stream, Z_NO_FLUSH);
        assert(ret != Z_STREAM_ERROR);
        switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void) inflateEnd(&stream);
        }
        int have = chunk - stream.avail_out;
        eventStream.resize(eventStream.size() + have);
        std::copy_n(out.get(), have, eventStream.end() - have);
    } while (stream.avail_out == 0);

    (void) inflateEnd(&stream);

    if (ret != Z_STREAM_END) {
        throw std::runtime_error("Inflator did not reach stream end");
    }

#ifdef _DEBUG
    {
        std::ofstream eventStreamOut("event_stream.dat", std::ios::beg | std::ios::binary);
        eventStreamOut.write(reinterpret_cast<const char*>(&eventStream[0]), eventStream.size());
        eventStreamOut.flush();
        eventStreamOut.close();
    }
#endif

    if (false) {// test code
        Json::Value packetArray(Json::arrayValue);
        auto it = eventStream.begin();
        while (it != eventStream.end()) {
            Packet packet(it);
            it += packet.size();
            packetArray.append(packet.toJson());
        }

        Json::StyledWriter writer;
        std::string json = writer.write(packetArray);
        std::ofstream eventStreamJson("event_stream.json", std::ios::binary);
        eventStreamJson.write(json.c_str(), json.size());
        eventStreamJson.flush();
        eventStreamJson.close();
    }
}

std::vector<std::string> Parser::extractJson(std::istream& is) {
    std::vector<DataBlock> dataBlocks(getDataBlocks(std::vector<uint8_t>(std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>())));

    int numberOfBlocks = dataBlocks.size();
    if (numberOfBlocks < 2) {
        throw new std::runtime_error("Unexpected number of blocks");
    }
    std::vector<std::string> json;
    // Don't export the last block, last block is raw replay data
    for (int i = 0; i < numberOfBlocks - 1; i++) {
        json.emplace_back(dataBlocks[i].getData().begin(), dataBlocks[i].getData().end());
    }
    return json;
}


bool Parser::isLegacy(const std::vector<uint8_t>& buffer) const {
    if (buffer.size() < 10) {
        throw new std::invalid_argument("Buffer is to small to process");
    }
    return buffer[8] == 0x78 && buffer[9] == 0xDA;
}

std::vector<DataBlock> Parser::getDataBlocks(std::vector<uint8_t> buffer) {
    if (isLegacy(buffer)) {
        throw new std::invalid_argument("No support for legacy replays");
    }

    const uint32_t blockCount = getDataBlockCount(buffer);
    std::cout << "data block count: " << blockCount << std::endl;

    std::vector<DataBlock> dataBlocks;

    uint32_t offset = 8; // Skip magic number and block count
    for (uint32_t i = 0; i < blockCount; i++) {
        const uint32_t blockSize = *reinterpret_cast<const uint32_t*>(&buffer[offset]);
        uint32_t blockOffset = offset + sizeof(uint32_t);
        dataBlocks.emplace_back(buffer.begin() + blockOffset, buffer.begin() + blockOffset + blockSize, blockSize);
        offset = blockOffset + blockSize;
    }

    // Last block contains encrypted gameplay data, seperated by 8 bytes
    uint32_t blockOffset = offset + 8;
    dataBlocks.emplace_back(buffer.begin() + blockOffset, buffer.end(), buffer.size() - blockOffset);

    return dataBlocks;
}

uint32_t Parser::getDataBlockCount(std::vector<uint8_t> buffer) {
    // Number of blocks is stored in after a offset of 4 bytes
    return (buffer[4] << 0) | (buffer[5] << 8) | (buffer[6] << 16) | (buffer[7] << 24);
}

}
