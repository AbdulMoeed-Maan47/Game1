cmake_minimum_required(VERSION 3.5)
project(Learning_SFML)

set(SOURCES
    src/main.cpp
)

include_directories(include)

set(SFML_DIR "C:/SFML/build")

find_package(SFML COMPONENTS graphics window system audio REQUIRED)

add_executable(Game1 ${SOURCES})

target_include_directories(Game1 PRIVATE include)

target_link_libraries(Game1 sfml-graphics sfml-window sfml-system sfml-audio)