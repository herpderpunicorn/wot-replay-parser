#include <vector>
#include <cstdint>
#include <json/json.h>

namespace WotReplayParser {

class UnPickle{
public:
    UnPickle() = default;
    UnPickle(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end);
    ~UnPickle() = default;
    Json::Value toJson() const;
private:
    std::vector<Json::Value> valueStack;
};

}