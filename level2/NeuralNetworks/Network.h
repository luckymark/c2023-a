//Network.h

#ifndef LEVEL2_NETWORK_H
#define LEVEL2_NETWORK_H

struct feat;
//函数声明
void sample_trans(struct feat input);
void para_reset();
void cal_r1();
void cal_r2();
void cal_r3();
double softmax(double input);
void cal_r4();
void Loss();
void cal_D_2();
double D_ReLU(double input);
void cal_D_1();
void Adam(double t);
int output();
void data_write();
void data_read();

#endif //LEVEL2_NETWORK_H