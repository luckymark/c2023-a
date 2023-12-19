project(gobang)

add_executable(chessboard chessboard.c
        Evaluate.c
        Evaluate.h
        Minimax_Search.c
        Minimax_Search.h
        Inspire_Search.c
        Inspire_Search.h
)

include_directories(gobang)

find_package(raylib)

target_link_libraries(chessboard raylib)
