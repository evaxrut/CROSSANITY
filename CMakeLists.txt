CMAKE_MINIMUM_REQUIRED(VERSION 3.22)

project(word_jumble)

set(CMAKE_CXX_STANDARD 17)       
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

set(FILES
    main.cpp
    src/utils.cpp
    src/Grid.cpp
    src/crossword.cpp
    src/Crosswords.cpp
    src/scoreboard.cpp
    src/WordList.cpp
    src/CrosswordGame.cpp
)

add_executable(word_jumble
    ${FILES}
)

target_include_directories(word_jumble
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)