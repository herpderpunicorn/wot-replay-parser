include(ExternalProject)

option(USE_GMOCK "If ON, not only gtest, but also gmock will be installed." OFF)

if (USE_GMOCK)
    ExternalProject_Add(gmock_ext
        URL "http://googlemock.googlecode.com/files/gmock-1.7.0.zip"
        BINARY_DIR "${CMAKE_BINARY_DIR}/third-party/gmock-build"
        SOURCE_DIR "${CMAKE_BINARY_DIR}/third-party/gmock-src"
        INSTALL_DIR "${CMAKE_BINARY_DIR}/third-party/gtest-build"
        CMAKE_ARGS "${gtest_cmake_args}"
            "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        INSTALL_COMMAND "")
  set(GTEST_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/third-party/gmock-src/gtest/include" "${CMAKE_BINARY_DIR}/third-party/gmock-src/include")
  link_directories("${CMAKE_BINARY_DIR}/third-party/gmock-build"
                   "${CMAKE_BINARY_DIR}/third-party/gmock-build/gtest")
else()
    ExternalProject_Add(gtest_ext
        URL "http://googletest.googlecode.com/files/gtest-1.7.0.zip"
        BINARY_DIR "${CMAKE_BINARY_DIR}/third-party/gtest-build"
        SOURCE_DIR "${CMAKE_BINARY_DIR}/third-party/gtest-src"
        INSTALL_COMMAND ""
        CMAKE_ARGS "${gtest_cmake_args}"
            "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
    set(GTEST_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/third-party/gtest-src/include")
    link_directories("${CMAKE_BINARY_DIR}/third-party/gtest-build")
endif()

enable_testing()

find_package(Threads)

function(cxx_test name sources working_dir)
    add_executable(${name} ${sources})
    target_link_libraries(${name} ${ARGN} gtest ${CMAKE_THREAD_LIBS_INIT})
    set_property(TARGET ${name} APPEND PROPERTY INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS})
    add_dependencies(${name} gmock_ext)
    add_test(NAME ${name} WORKING_DIRECTORY ${working_dir} COMMAND ${name} --gtest_break_on_failure)
endfunction()

