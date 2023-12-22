project(level1)

add_executable(p01_running_letter p01_running_letter/main.c)

add_executable(p02_is_prime p02_is_prime/main.c p02_is_prime/prime.c)

add_executable(p03_all_primes p03_all_primes/main.c p03_all_primes/prime.c)

add_executable(p04_goldbach p04_goldbach/main.c)

add_executable(p05_encrypt_decrypt p05_encrypt_decrypt/main.c)

add_executable(p06_hanoi p06_hanoi/main.cpp)

add_executable(p07_maze p07_maze/main.c p07_maze/maze.c)

add_executable(p08_push_boxes p08_push_boxes/main.c p08_push_boxes/push_boxes.c)

add_executable(p09_linked_list p09_linked_list/main.c p09_linked_list/linked.c)

add_executable(p10_warehouse p10_warehouse/main.c
        p10_warehouse/warehouse.c)
