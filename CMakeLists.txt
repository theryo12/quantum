cmake_minimum_required(VERSION 3.21)

project(quantum LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE CPP_SOURCES src/*.cpp)
file(GLOB_RECURSE IXX_SOURCES src/*.ixx)

find_program(CLANG_TIDY_EXE NAMES clang-tidy)

if(CLANG_TIDY_EXE)
    message(STATUS "Found clang-tidy: ${CLANG_TIDY_EXE}")
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};--fix")
endif()


include_directories(include)

if (WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/lib/SFML/include)

    set(SFML_LIB_DIR ${CMAKE_SOURCE_DIR}/lib/SFML/lib)
    link_directories(${SFML_LIB_DIR})

    set(SFML_LIBS sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
else()
    find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
    set(SFML_LIBS sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
endif()

add_executable(quantum ${CPP_SOURCES} ${IXX_SOURCES})

target_link_libraries(quantum ${SFML_LIBS})

set_target_properties(quantum PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
)

if (WIN32)
    file(COPY "${SFML_LIB_DIR}/sfml-graphics-2.dll" DESTINATION "${CMAKE_BINARY_DIR}/bin")
    file(COPY "${SFML_LIB_DIR}/sfml-window-2.dll" DESTINATION "${CMAKE_BINARY_DIR}/bin")
    file(COPY "${SFML_LIB_DIR}/sfml-system-2.dll" DESTINATION "${CMAKE_BINARY_DIR}/bin")
    file(COPY "${SFML_LIB_DIR}/sfml-audio-2.dll" DESTINATION "${CMAKE_BINARY_DIR}/bin")
    file(COPY "${SFML_LIB_DIR}/sfml-network-2.dll" DESTINATION "${CMAKE_BINARY_DIR}/bin")
endif()
