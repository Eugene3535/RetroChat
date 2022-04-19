cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME RetroChat)
project(${PROJECT_NAME})

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
 SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(
 ${PROJECT_NAME}
 source/main.cpp
)

target_link_libraries(
 ${PROJECT_NAME}
 sfml-graphics
 sfml-window
 sfml-system
 sfml-audio
 sfml-network
)