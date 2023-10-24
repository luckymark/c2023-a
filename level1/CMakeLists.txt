project(level1)
add_compile_options(-finput-charset=utf-8 -fexec-charset=gbk)
add_executable(p01_running_letter p01_running_letter/main.c)

add_executable(p02_is_prime p02_is_prime/main.c)

add_executable(p03_all_primes p03_all_primes/main.c
        p03_all_primes/isPrime.h
        p03_all_primes/isPrime.h
        p03_all_primes/isPrime.c)

add_executable(p04_goldbach p04_goldbach/main.c)

add_executable(p05_encrypt_decrypt p05_encrypt_decrypt/main.c)

add_executable(p06_hanoi p06_hanoi/main.c)

add_executable(p07_maze p07_maze/main.c)

add_executable(p08_push_boxes p08_push_boxes/main.c
        p08_push_boxes/gameFunction.c
        p08_push_boxes/gameFunction.h
        p08_push_boxes/shellControl.h
        p08_push_boxes/shellControl.c
        p08_push_boxes/maploader.c
        p08_push_boxes/maploader.h)

add_executable(p09_linked_list p09_linked_list/main.c
        p09_linked_list/linked_list.c
        p09_linked_list/linked_list.h)

add_executable(p10_warehouse p10_warehouse/main.c
        p10_warehouse/shellControl.c
        p10_warehouse/shellControl.h
        p10_warehouse/function.c
        p10_warehouse/function.h)