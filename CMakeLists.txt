cmake_minimum_required(VERSION 3.20)
project(base_encoder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# base32 lib

add_library(base32
        lib/base32/base32.h
        lib/base32/decoding/decoding.h
        lib/base32/encoding/encoding.h
        lib/base32/decoding/decoding.cpp
        lib/base32/encoding/encoding.cpp
        lib/base32/utility/utility.h
        lib/base32/utility/utility.cpp
)

set_target_properties(base32 PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(base32 PUBLIC lib/base32)

# app

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTKMM gtkmm-3.0 REQUIRED)

link_directories(
        ${GTKMM_LIBRARY_DIRS}
)

include_directories(
        ${GTKMM_INCLUDE_DIRS}
)

add_executable(base_encoder
        app/app.cpp
)

target_include_directories(base_encoder PRIVATE lib)

target_link_libraries(base_encoder
        ${GTKMM_LIBRARIES}
        base32
)

# test

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(base32test test/base32/base32test.cpp
        test/base32/base32test.cpp)
target_link_libraries(base32test base32 gtest gtest_main)
target_include_directories(base32test PRIVATE lib/)

include(GoogleTest)

gtest_discover_tests(base32test)
