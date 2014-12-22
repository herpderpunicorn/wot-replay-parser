cmake_minimum_required(VERSION 2.8.4)
project(wot-replay-parser-tests)

include(GTest.cmake)
set(TEST_FILES Version.cc BattleResult.cc BattleSetup.cc DataBlock.cc)
cxx_test(unitTests "${TEST_FILES}" gtest_main wot-replay-parser cryptopp)
