cmake_minimum_required(VERSION 3.2)
project(c2023_challenge)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(level1)
add_executable(new_target
        level0/bubbleSort/sort.c
        level0/bubbleSort/main.c
        level0/bubbleSort/sort.h
        level0/caculater/calculator.c
        level0/caculater/calculator.h)
add_executable(queue
        level0/Queue/queue.c
        level0/Queue/queue.h
        level0/Queue/main.c
        level0/Queue/LifoQueue.c
        level0/Queue/LifoQueue.h)
add_executable(caculater level0/caculater/calculator.c level0/caculater/calculator.h
        level0/caculater/main.c
        level0/caculater/LifoQueue.c
        level0/hashMap/HashMap.cpp
        level0/hashMap/HashMap.h)
add_executable(BigNum level0/BigNum/main.c
        level0/BigNum/BigNum.c
        level0/BigNum/BigNum.h)
