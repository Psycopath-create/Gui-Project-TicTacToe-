cmake_minimum_required(VERSION 3.20)
project(TicTacToeSFML LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
)

FetchContent_MakeAvailable(SFML)

add_executable(tic_tac_toe_sfml
    main.cpp
    drawing.cpp
    input_handler.cpp
    game_logic.cpp
    stats.cpp
)

target_link_libraries(tic_tac_toe_sfml PRIVATE sfml-graphics sfml-window sfml-system)
