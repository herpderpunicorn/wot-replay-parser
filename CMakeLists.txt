cmake_minimum_required(VERSION 2.8.4)
project(wot-replay-parser)

include_directories(./JsonCpp/ ./ext/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_library(wot-replay-parser STATIC BattleResult.cpp BattleSetup.cpp DataBlock.cpp GameState.cpp GameVersion.cpp MatchData.cpp MatchStart.cpp Packet.cpp Parser.cpp Personal.cpp RoamingSettings.cpp Vehicle.cpp Version.cpp)

install(TARGETS wot-replay-parser DESTINATION lib)
install(FILES GameVersion.hpp DESTINATION include)
