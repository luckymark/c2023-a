//
// Created by Administrator on 2023/9/27 0027.
//

#ifndef LEVEL2_EXTRACT_METHODS_H
#define LEVEL2_EXTRACT_METHODS_H
int bigger(int,int);
int bitReverse(int);
double FFT(double f[8]);
double extract_x_cen(int input[8][8]);
double extract_y_cen(int input[8][8]);
int scan_0(int input[8][8]);
int scan_90(int input[8][8]);
int scan_45(int input[8][8]);
int scan_135(int input[8][8]);
double* EFT(int input[8][8]);
#endif //LEVEL2_EXTRACT_METHODS_H
