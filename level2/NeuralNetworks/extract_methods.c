//
// Created by Administrator on 2023/9/27 0027.
//

#include "extract_methods.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#define N 8
int bigger(int a, int b) {
    return a>b?a:b;
}
int bitReverse(int i) {
    int j = 0;
    for (int k = 0; k < N; k++) {
        j <<= 1;
        j |= (i >> k) & 1;
    }
    return j;
}
//快速傅里叶变换
double FFT(double f[N]) {
    double F[N];
    for (int i = 0; i < N; i++) {
        F[i] = f[bitReverse(i)];
    }
    for (int s = 1; s < log2(N); s++) {
        int m = 1 << s;
        for (int k = 0; k < N; k+=m) {
            double w = cos(2*M_PI*k/m) - sin(2*M_PI*k/m);
            for (int i = 0; i < m/2; i++) {
                double t = w * F[k+m/2+i];
                F[k+m/2+i] = F[k+i] - t;
                F[k+i] += t;
            }
        }
    }
    double result = 0;
    for (int i = 0; i < N; i++) {
        result += sqrt(F[i]*F[i]);
    }
    return result;
}
//质心
double extract_x_cen(int input[N][N]) {
    int I_sum = 0;
    int x_sum = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            x_sum += input[i][j]*(j+1);
            I_sum += input[i][j];
        }
    }
    return (double)x_sum / I_sum;
}
double extract_y_cen(int input[N][N]) {
    int I_sum = 0;
    int y_sum = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            y_sum += input[i][j] * (i + 1);
            I_sum += input[i][j];
        }
    }
    return (double)y_sum / I_sum;
}
//扫描线
int scan_0(int input[N][N]) {
    int result = 0;
    for (int i = 0; i < N; ++i) {
        int k = 0;
        for (int j = 0; j < N; ++j) {
            k += input[i][j];
        }
        result = bigger(result, k);
    }
    return result;
}
int scan_90(int input[N][N]) {
    int result = 0;
    for (int i = 0; i < N; ++i) {
        int k = 0;
        for (int j = 0; j < N; ++j) {
            k += input[j][i];
        }
        result = bigger(result, k);
    }
    return result;
}
int scan_45(int input[N][N]) {
    int result = 0;
    //01~07
    for (int i = 0; i < 8; ++i) {
        int l = 0;
        int k =0;
        for (int j = i; j >= 0; --j) {
            l += input[k][j];
            k++;
        }
        result = bigger(result, l);
    }
    //17~77
    for (int i = 1; i < 8; ++i) {
        int  l = 0;
        int k =i;
        for (int j = 7; j >= i; --j) {
            l += input[k][j];
            k++;
        }
        result = bigger(result, l);
    }
    return result;
}
int scan_135(int input[N][N]) {
    //特征 6: 135°扫描线
    int result = 0;
    for (int i = 0; i < 8; ++i) {
        int l = 0;
        int k = 7;
        for (int j = i; j < 8; ++j) {
            l += input[k][j];
            k--;
        }
        result = bigger(result, l);
    }
    for (int i = 1; i < 8; ++i) {
        int l = 0;
        int k = i - 1;
        for (int j = 0; j <= i; ++j) {
            l += input[k][j];
            k--;
        }
        result = bigger(result, l);
    }
    return result;
}
//获取傅里叶特征
double* EFT(int input[N][N]) {
    double* FEATURES = (double*) malloc(N*sizeof(double));
    //傅里叶特征提取
    double f[N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            f[j] = input[i][j];
        }
        FEATURES[i] = FFT(f);
    }
    return FEATURES;
}