#include "UnPickle.hpp"

/** this is from python cPickle.c */

/* Bump this when new opcodes are added to the pickle protocol. */
#define HIGHEST_PROTOCOL 2

/*
 * Pickle opcodes.  These must be kept in synch with pickle.py.  Extensive
 * docs are in pickletools.py.
 */
#define MARK        '('
#define STOP        '.'
#define POP         '0'
#define POP_MARK    '1'
#define DUP         '2'
#define FLOAT       'F'
#define BINFLOAT    'G'
#define INT         'I'
#define BININT      'J'
#define BININT1     'K'
#define LONG        'L'
#define BININT2     'M'
#define NONE        'N'
#define PERSID      'P'
#define BINPERSID   'Q'
#define REDUCE      'R'
#define STRING      'S'
#define BINSTRING   'T'
#define SHORT_BINSTRING 'U'
#define UNICODE     'V'
#define BINUNICODE  'X'
#define APPEND      'a'
#define BUILD       'b'
#define GLOBAL      'c'
#define DICT        'd'
#define EMPTY_DICT  '}'
#define APPENDS     'e'
#define GET         'g'
#define BINGET      'h'
#define INST        'i'
#define LONG_BINGET 'j'
#define LIST        'l'
#define EMPTY_LIST  ']'
#define OBJ         'o'
#define PUT         'p'
#define BINPUT      'q'
#define LONG_BINPUT 'r'
#define SETITEM     's'
#define TUPLE       't'
#define EMPTY_TUPLE ')'
#define SETITEMS    'u'

/* Protocol 2. */
#define PROTO	 '\x80' /* identify pickle protocol */
#define NEWOBJ   '\x81' /* build object by applying cls.__new__ to argtuple */
#define EXT1     '\x82' /* push object from extension registry; 1-byte index */
#define EXT2     '\x83' /* ditto, but 2-byte index */
#define EXT4     '\x84' /* ditto, but 4-byte index */
#define TUPLE1   '\x85' /* build 1-tuple from stack top */
#define TUPLE2   '\x86' /* build 2-tuple from two topmost stack items */
#define TUPLE3   '\x87' /* build 3-tuple from three topmost stack items */
#define NEWTRUE  '\x88' /* push True */
#define NEWFALSE '\x89' /* push False */
#define LONG1    '\x8a' /* push long from < 256 bytes */
#define LONG4    '\x8b' /* push really big long */

namespace WotReplayParser {
UnPickle::UnPickle(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end) {
    while (begin != end) {
        const int8_t code = *begin++;
        switch (code) {
            case PROTO: {
                    const uint8_t version = *begin;
                    if (version < 0 || version > HIGHEST_PROTOCOL) {
                        throw std::runtime_error("Invalid proto version in pickle");
                    }
                    ++begin;
                }
                break;
            case BINPUT:
                ++begin;
                break;
            case SHORT_BINSTRING: {
                    const uint8_t len = *begin++;
                    std::string s(begin, begin+len);
                    valueStack.emplace_back(Json::Value(s));
                    begin += len;
                }
                break;
            case EMPTY_DICT:
                valueStack.emplace_back(Json::Value(Json::objectValue));
                break;
            case BININT1:
                valueStack.emplace_back(Json::Value(*begin));
                ++begin;
                break;
            case SETITEM: {
                    const size_t top = valueStack.size()-1;
                    Json::Value& object = valueStack.at(top - 2);
                    Json::Value key = valueStack.at(top - 1);
                    Json::Value value = valueStack.at(top);
                    object[key.asString()] = value;
                    valueStack.resize(valueStack.size()-top);
                }
                break;
            case STOP:
                break;
            default:
                throw std::runtime_error("Unknown opcode");

        }
    }
}

Json::Value UnPickle::toJson() const {
    if (!valueStack.empty()) return valueStack.at(0);
    return Json::Value(Json::nullValue);
}
}
