cmake_minimum_required(VERSION 3.10)
project(ConwaysGOLcpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ConwaysGOLcpp
    src/main.cpp
    src/game_of_life.cpp
    src/game_app.cpp
)

find_package(SDL2 REQUIRED)

target_include_directories(ConwaysGOLcpp PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(ConwaysGOLcpp PRIVATE ${SDL2_LIBRARIES})

add_custom_command(TARGET ConwaysGOLcpp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:ConwaysGOLcpp> ${CMAKE_SOURCE_DIR}
)
