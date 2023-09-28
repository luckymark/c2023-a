//
// Created by Administrator on 2023/9/26 0026.
//
int is_prime(int input_num) {
    if(input_num==2) {
        return 1;
    } else {
        for (int i = 2; i < input_num; ++i) {
            if (input_num % i == 0) {
                return 0;
            }
        }
        return 1;
    }
}
