# CMake build script for C++ Basic Project Setup Example
cmake_minimum_required(VERSION 3.0.2)

project(cpp_basic_project_setup)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Enable more warnings
set(CXX_EXTRA_FLAGS "-Wall -Wextra -pedantic -Woverloaded-virtual \
                    -Wmissing-declarations -Wnon-virtual-dtor -fpermissive ")

# Debug by default has '-g'
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_EXTRA_FLAGS} -O0")
# Release by default has '-O3 -DNDEBUG'
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_EXTRA_FLAGS}")
# Make Debug default build type
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}")

# CYGWIN requirements: we need gnu++14 instead of c++14
if(CYGWIN OR MINGW)
  add_compile_options( -std=gnu++14 )
  option(gtest_disable_pthreads "Disable uses of pthreads in gtest." ON)
else()
  add_compile_options( -std=c++14 )
endif()

# Google Dependencies require pthread if gnu g++
if(CMAKE_COMPILER_IS_GNUCXX)
  add_compile_options(-pthread)
endif()

add_subdirectory(
  ./3rdparty/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest EXCLUDE_FROM_ALL)

# Include necessary directories
include_directories(${gtest_SOURCE_DIR}/include)
include_directories(${gmock_SOURCE_DIR}/include)
include_directories(src)

# Treat warnings as errors in our own code
add_compile_options(-Werror)

# Build our library
add_library(business_logic
  src/business_logic/temperature_monitor.cpp
  src/data_providers/unimplemented_network_storage.cpp
)

# Unit tests for our business_logic library
# add_executable(${PROJECT_NAME}_tests EXCLUDE_FROM_ALL
#   test/mocks.cpp,
#   test/temperature_monitor_test.cpp
# )
# Standard linking to gtest & gmock stuff and our own library
# target_link_libraries(${PROJECT_NAME}_tests business_logic gtest gmock gmock_main)

# Target for code analysis
add_custom_target(${PROJECT_NAME}_lint ${CMAKE_CURRENT_SOURCE_DIR}/verify_cpp_code.sh)

# Target for running unit tests and code style analysis
add_custom_target(tests
  # COMMAND ./${PROJECT_NAME}_tests
  DEPENDS ${PROJECT_NAME}_lint
)
