cmake_minimum_required(VERSION 3.28)
project(NUMBERRECOGNIZER LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(src/lib/include)
file(GLOB SOURCES "src/lib/*.cpp")

set(HIDE_TERMINAL OFF)
# NOTE:  Setting this to 'ON' prevents printing to the terminal! 
#        when Debugging, set to 'OFF'

if(HIDE_TERMINAL)
    add_executable(main WIN32 src/main.cpp ${SOURCES})
else()
    add_executable(main src/main.cpp ${SOURCES})
endif()
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
