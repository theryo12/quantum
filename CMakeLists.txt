# minimum required CMake version
cmake_minimum_required(VERSION 3.15)

# project name and version
project(Quantum VERSION 1.0 LANGUAGES CXX)

# specify C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# locate SDL2
find_package(SDL2 REQUIRED)

# options for build customization
option(QUANTUM_DEBUG "Enable Debugging Mode with additional logging" OFF)
option(QUANTUM_SANITIZERS "Enable Address and Undefined Behavior Sanitizers for Debugging" OFF)
option(QUANTUM_LTO "Enable Link-Time Optimization for enhanced performance" ON)
option(QUANTUM_ARCH_OPT "Enable CPU-specific optimizations" ON)
option(QUANTUM_WARNINGS "Enable strict compiler warnings and treat them as errors" ON)

# source files in src directory
file(GLOB SRC_FILES src/*.cpp)

# create executable
add_executable(Quantum ${SRC_FILES})

# include SDL2 headers and link SDL2 library
target_include_directories(Quantum PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(Quantum PRIVATE ${SDL2_LIBRARIES})

# configure debugging options
if(QUANTUM_DEBUG)
    message(STATUS "Debug mode enabled with debug symbols and reduced optimizations.")
    target_compile_options(Quantum PRIVATE -g -O0)
    target_compile_definitions(Quantum PRIVATE DEBUG_MODE=1)
else()
    message(STATUS "Release mode: enabling high optimizations.")
    target_compile_options(Quantum PRIVATE -O3) # high optimization for release builds
endif()

# enable sanitizers if required (helpful for memory safety checks)
if(QUANTUM_SANITIZERS AND QUANTUM_DEBUG)
    message(STATUS "Enabling sanitizers for debugging.")
    target_compile_options(Quantum PRIVATE -fsanitize=address -fsanitize=undefined)
    target_link_options(Quantum PRIVATE -fsanitize=address -fsanitize=undefined)
endif()

# enable link-time optimization (LTO) if required
if(QUANTUM_LTO AND NOT QUANTUM_DEBUG)
    message(STATUS "Link-Time Optimization (LTO) enabled for improved performance.")
    set_target_properties(Quantum PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

# enable architecture-specific optimizations
if(QUANTUM_ARCH_OPT AND NOT QUANTUM_DEBUG)
    message(STATUS "Enabling architecture-specific optimizations.")
    target_compile_options(Quantum PRIVATE -march=native)
endif()

# enable strict warnings
if(QUANTUM_WARNINGS)
    message(STATUS "Strict warnings enabled.")
    target_compile_options(Quantum PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

# add resources directory if exists
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/resources)
if(EXISTS ${RESOURCES_DIR})
    message(STATUS "Resources directory detected and included.")
    target_compile_definitions(Quantum PRIVATE RESOURCES_PATH="${RESOURCES_DIR}")
else()
    message(WARNING "Resources directory not found. Proceeding without additional resources.")
endif()

# -------- Google Test Integration --------
# Download Google Test if not found
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# enable testing in CMake
enable_testing()
FetchContent_MakeAvailable(googletest)

# find all test files in tests directory
file(GLOB TEST_FILES tests/*.cpp)

# add each test file as a separate executable and register with CTest
foreach(TEST_FILE ${TEST_FILES})
    # extract test name from file name
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    
    # create an executable for the test
    add_executable(${TEST_NAME} ${TEST_FILE})
    
    # link with Google Test and SDL2 libraries
    target_link_libraries(${TEST_NAME} PRIVATE gtest_main ${SDL2_LIBRARIES})
    
    # register the test with CTest
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# custom output build information
message(STATUS "Quantum Game Project CMake Configuration:")
message(STATUS "  C++ Standard: C++20")
message(STATUS "  SDL2 found and linked")
message(STATUS "  Debug Mode: ${QUANTUM_DEBUG}")
message(STATUS "  Sanitizers: ${QUANTUM_SANITIZERS}")
message(STATUS "  Link-Time Optimization (LTO): ${QUANTUM_LTO}")
message(STATUS "  Architecture-specific optimizations: ${QUANTUM_ARCH_OPT}")
message(STATUS "  Strict Warnings: ${QUANTUM_WARNINGS}")