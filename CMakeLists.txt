cmake_minimum_required(VERSION 2.8.4)
project(wot-replay-parser)

include_directories(./JsonCpp/ ./ext/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES BattleResult.cpp BattleSetup.cpp DataBlock.cpp GameState.cpp GameVersion.cpp MatchData.cpp MatchStart.cpp Packet.cpp Parser.cpp Personal.cpp RoamingSettings.cpp Vehicle.cpp Version.cpp)
set(INCLUDE_FILES BattleResult.hpp BattleSetup.hpp Common.hpp DataBlock.hpp GameState.hpp GameVersion.hpp MatchData.hpp MatchStart.hpp Packet.hpp Packets.hpp Parser.hpp Payload.hpp Personal.hpp RoamingSettings.hpp Vehicle.hpp Version.hpp)
add_library(wot-replay-parser STATIC ${SOURCE_FILES})

install(TARGETS wot-replay-parser DESTINATION lib)
install(FILES ${INCLUDE_FILES} DESTINATION include)
