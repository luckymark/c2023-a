cmake_minimum_required(VERSION 3.26)

project(gobang C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-finput-charset=utf-8 -fexec-charset=gbk -mwindows -lpthread)

find_package(raylib)

add_executable(gobang "work/Former Codes/main.c")
target_link_libraries(${PROJECT_NAME} raylib)

add_executable(work work/test.c
        work/stack_point.c
        work/stack_point.h
        work/linked_hash_value_list.c
        work/linked_hash_value_list.c
        work/linked_hash_value_list.h
        work/MT199937.c
        work/MT199937.h
        work/hash_table.c
        work/hash_table.h
        work/Zobrist.c
        work/Zobrist.h
        work/evaluate_func.c
        work/evaluate_func.h
        work/board_control.c
        work/board_control.h
        work/generate.c
        work/generate.h)
target_link_libraries(work raylib)

add_executable(gui work/gui.c
        work/stack_point.c
        work/stack_point.h
        work/test.c
        work/test.h
        work/defination.h
        work/linked_hash_value_list.c
        work/linked_hash_value_list.h
        work/MT199937.c
        work/MT199937.h
        work/hash_table.c
        work/hash_table.h
        work/Zobrist.c
        work/Zobrist.h
        work/evaluate_func.c
        work/evaluate_func.h
        work/board_control.c
        work/board_control.h
        work/generate.c
        work/generate.h)
target_link_libraries(gui raylib)

set(CMAKE_BUILD_TYPE Release)

#set (CMAKE_C_FLAGS "-mwindows")