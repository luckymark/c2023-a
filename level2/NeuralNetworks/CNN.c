/*
 * 卷积层
 */



#include "CNN.h"

#define N 8

void CNN(int input[N][N]) {
    //对输入的图像进行加边
    int input_[N+2][N+2] = {0};
    for (int i = 1; i < 8; ++i) {
        for (int j = 1; j < 8; ++j) {
            input_[i][j] = input[i-1][j-1];
        }
    }

}