//
// Created by Administrator on 2023/10/4 0004.
//
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "Network.h"

//隐层节点数
#define N_ 8
//特征向量大小
#define M_ 14
//类型数量
#define C_ 10
//Adam算法超参数
#define Alpha 0.01 //步长参数(学习率)
#define Beta_1 0.9 //一阶矩估计指数衰减率
#define Beta_2 0.99 //二阶矩估计指数衰减率
#define Epsilon 0.00000001 //分母稳定性参数

struct feat {
    //x质心
    double x_cen;
    //y质心
    double y_cen;
    //扫描线
    int count[8];
    //傅里叶特征
    double* fft;
    //标签
    int label;
};
//各参数
double W1[N_][M_], W2[C_][N_], B1[N_], B2[C_];
//Loss对各参数的导数
double D_W2[C_][N_], D_B2[C_], D_W1[N_][M_], D_B1[N_];
//计算过程中的结果，代表y1,y2,y3,y4以及损失函数的值
double result_1[N_], result_2[N_], result_3[C_], result_4[C_], loss;
//由标签转化的one-hot向量
double y_true[C_];
//算法输入，特征向量
double X[M_];
//求导中间值
double Dy1_DW1[N_*N_][M_], Dy1_Db1[N_*N_], Dy2_Dy1[N_*N_], DL_Dy2[N_];
//各参数的一、二阶矩估计(m为一阶,v为二阶)
double m_W1[N_][M_], v_W1[N_][M_], m_B1[N_], v_B1[N_], m_W2[C_][N_], v_W2[C_][N_], m_B2[C_], v_B2[C_];
//输入特征向量，转化为输入数据X，程序起点
void sample_trans(struct feat input) {
    //将输入的特征向量转化为单一数组
    X[0] = (double)input.x_cen;
    X[1] = (double)input.y_cen;
    for (int i = 2; i <6; ++i) {
        X[i] = (double)input.count[i-2];
    }
    for (int i = 6; i < 14; ++i) {
        X[i] = input.fft[i-6];
    }
    //将标签转化为one-hot列向量
    for (int i = 0; i < C_; ++i) {
        if(i==input.label) {
            y_true[i] = 1;
        } else {
            y_true[i] = 0;
        }
    }
}
//ReLU激活函数
double ReLU(double input) {
    return input>0?input:0;
}
//参数初始化
void para_reset() {
    for (int i = 0; i < N_; ++i) {
        B1[i] = 0;
        v_B1[i] = 0;
        m_B1[i] = 0;
    }
    for (int i = 0; i < C_; ++i) {
        B2[i] = 0;
        v_B2[i] = 0;
        m_B2[i] = 0;
    }
    for (int i = 0; i < N_; ++i) {
        for (int j = 0; j < M_; ++j) {
            srand(rand());
            double num = (double)rand()/RAND_MAX;
            W1[i][j] = -0.1+num*(0.2);
            v_W1[i][j] = 0;
            m_W1[i][j] = 0;
        }
    }
    for (int i = 0; i < C_; ++i) {
        for (int j = 0; j < N_; ++j) {
            srand(rand());
            double num = (double)rand()/RAND_MAX;
            W2[i][j] = -0.1+num*(0.2);
            v_W2[i][j] = 0;
            m_W2[i][j] = 0;
        }
    }
}
//计算 y1(result_1) = W1*X + B1
void cal_r1() {
    for (int i = 0; i < N_; ++i) {
        result_1[i] = 0;
        for (int j = 0; j < M_; ++j) {
            result_1[i] += W1[i][j]*X[j];
        }
        result_1[i] += B1[i];
    }
}
//计算 y2(result_2) = ReLU(y1)，隐藏层
void cal_r2() {
    for (int i = 0; i < N_; ++i) {
        result_2[i] = ReLU(result_1[i]);
    }
}
//计算 y3 = W2*y2 + B2
void cal_r3() {
    for (int i = 0; i < C_; ++i) {
        result_3[i] = 0;
        for (int j = 0; j < N_; ++j) {
            result_3[i] += W2[i][j]*result_2[j];
        }
        result_3[i] += B2[i];
    }
}
//softmax激活函数
double softmax(double input) {
    double sum = 0;
    for (int i = 0; i < C_; ++i) {
        sum += exp(result_3[i]);
    }
    return exp(input) / sum;
}
//计算 y4 = softmax(y3)
void cal_r4() {
    for (int i = 0; i < C_; ++i) {
        result_4[i] = softmax(result_3[i]);
    }
}
//损失函数
void Loss() {
    loss = 0;
    for (int i = 0; i < C_; ++i) {
        loss += -y_true[i]*log(result_4[i]);
    }
}
//计算DL/DW2与DL/DB2，DL/Dy2，三者计算方式相近
void cal_D_2() {
    //此处计算DL/DB2
    for (int i = 0; i < C_; ++i) {
        D_B2[i] = y_true[i] + result_4[i];
    }
    //计算DL/DW2,DL/Dy2
    for (int i = 0; i < C_; ++i) {
        for (int j = 0; j < N_; ++j) {
            D_W2[i][j] = D_B2[i]* result_2[j];
        }
    }
    for (int i = 0; i < N_; ++i) {
        for (int j = 0; j < C_; ++j) {
            DL_Dy2[i] = W2[j][i] * D_B2[i];
        }
    }
}
//求ReLU函数的导数
double D_ReLU(double input) {
    return input > 0 ? 1 : 0;
}
/* 此处将用链式传播法则求DL/DW1与DL/DB1
 * 以下记录吐槽
 * 最初我将所有式子代入损失函数
 * 得到式子：Loss = -y_true * Log(softmax(W2*ReLU(W1*x+B1)+B1))
 * 试图在式子中直接求导
 * 最后发现tmd维数不相容了，迫不得已采用链式传播法则
 * 说实话，向量对矩阵的求导在网上太难找了
 * 多方求助最终才推导出公式，真的很难！！！！！
 * Ps: 关于矩阵求导与FFT等在此处常用的算法，建议阅读《矩阵分析与应用》
 */
void cal_D_1() {
    //求Dy1/DW1
    for (int i = 1; i <= N_; ++i) {
        for (int j = (i-1)*N_; j < i*N_; ++j) {
            for (int k = 0; k < M_; ++k) {
                if(j == (i-1)*N_+(i-1)) {
                    Dy1_DW1[j][k] = X[k];
                } else {
                    Dy1_DW1[j][k] = 0;
                }
            }
        }
    }
    //求Dy1/DB1
    for (int i = 0; i < N_; ++i) {
        for (int j = (i-1)*N_; j < i*N_; ++j) {
            if(j == (i-1)*N_+(i-1)) {
                Dy2_Dy1[j] = 1;
            } else {
                Dy2_Dy1[j] = 0;
            }
        }
    }
    //求Dy2/Dy1
    for (int i = 0; i < N_; ++i) {
        for (int j = (i-1)*N_; j < i*N_; ++j) {
            if(j == (i-1)*N_+(i-1)) {
                Dy2_Dy1[j] = D_ReLU(result_1[i]);
            } else {
                Dy2_Dy1[j] = 0;
            }
        }
    }
    //由链式法则求part=DL/Dy2*(Dy2/Dy1)T
    double part[N_][N_*N_];
    for (int i = 0; i < N_*N_; ++i) {
        for (int j = 0; j < N_; ++j) {
            part[j][i] = DL_Dy2[j]*Dy2_Dy1[i];
        }
    }
    //由链式法则求DL/DW1,DL/DB1
    for (int i = 0; i < N_; ++i) {
        D_B1[i] = 0;
        for (int j = 0; j < M_; ++j) {
            D_W1[i][j] = 0;
        }
    }
    for (int i = 0; i < N_; ++i) {
        for (int j = 0; j < M_; ++j) {
            for (int k = 0; k < N_*N_; ++k) {
                D_W1[i][j] += part[i][k]*Dy1_DW1[k][j];
            }
        }
    }
    for (int i = 0; i < N_; ++i) {
        for (int j = 0; j < N_*N_; ++j) {
            D_B1[i] += part[i][j]*Dy1_Db1[j];
        }
    }
}
//自适应学习率梯度下降
void Adam(double t) {
    //各参数的一、二阶矩估计
    for (int i = 0; i < N_; ++i) {
        m_B1[i] = Beta_1*m_B1[i] + (1-Beta_1)*D_B1[i];
        v_B1[i] = Beta_2*m_B1[i] + (1-Beta_2)*D_B1[i]*D_B1[i];
        for (int j = 0; j < M_; ++j) {
            m_W1[i][j] = Beta_1*m_W1[i][j] + (1-Beta_1)*D_W1[i][j];
            v_W1[i][j] = Beta_2*m_W1[i][j] + (1-Beta_2)*D_W1[i][j]*D_W1[i][j];
        }
    }
    for (int i = 0; i < C_; ++i) {
        m_B2[i] = Beta_1*m_B2[i] + (1-Beta_1)*D_B2[i];
        v_B2[i] = Beta_2*m_B2[i] + (1-Beta_2)*D_B2[i]*D_B2[i];
        for (int j = 0; j < N_; ++j) {
            m_W2[i][j] = Beta_1*m_W2[i][j] + (1-Beta_1)*D_W2[i][j];
            v_W2[i][j] = Beta_2*m_W2[i][j] + (1-Beta_2)*D_W2[i][j]*D_W2[i][j];
        }
    }
    //修正矩估计
    for (int i = 0; i < N_; ++i) {
        m_B1[i] = m_B1[i]/(1- pow(Beta_1,t));
        v_B1[i] = v_B1[i]/(1- pow(Beta_2,t));
        for (int j = 0; j < M_; ++j) {
            m_W1[i][j] = m_W1[i][j]/(1- pow(Beta_1,t));
            v_W1[i][j] = v_W1[i][j]/(1- pow(Beta_2,t));
        }
    }
    for (int i = 0; i < C_; ++i) {
        m_B2[i] = m_B2[i]/(1- pow(Beta_1,t));
        v_B2[i] = v_B2[i]/(1- pow(Beta_2,t));
        for (int j = 0; j < N_; ++j) {
            m_W2[i][j] = m_W2[i][j]/(1- pow(Beta_1,t));
            v_W2[i][j] = v_W2[i][j]/(1- pow(Beta_2,t));
        }
    }
    //梯度下降
    for (int i = 0; i < N_; ++i) {
        B1[i] = B1[i] - (Alpha*m_B1[i]/(sqrt(v_B1[i])+Epsilon))*D_B1[i];
        for (int j = 0; j < M_; ++j) {
            W1[i][j] = W1[i][j] - (Alpha*m_W1[i][j]/(sqrt(v_W1[i][j])+Epsilon))*D_W1[i][j];
        }
    }
    for (int i = 0; i < C_; ++i) {
        B2[i] = B2[i] - (Alpha*m_B2[i]/(sqrt(v_B2[i])+Epsilon))*D_B2[i];
        for (int j = 0; j < N_; ++j) {
            W2[i][j] = W2[i][j] - (Alpha*m_W2[i][j]/(sqrt(v_W2[i][j])+Epsilon))*D_W2[i][j];
        }
    }
}
//输出判断结果
int output() {
    double max = 0;
    int out = 0;
    for (int i = 0; i < C_; ++i) {
        max = max>result_4[i] ? max : result_4[i];
    }
    for (int i = 0; i < C_; ++i) {
        if (result_4[i] == max) {
            out = i;
        }
    }
    return out;
}
//将各参数数据写入文件"parameter.dat"
void data_write() {
    FILE* fp;
    fp = fopen("parameter.dat","wb");
    for (int i = 0; i < N_; ++i) {
        for (int j = 0; j < M_; ++j) {
            fwrite(&W1[i][j],sizeof(double),1,fp);
        }
    }
    for (int i = 0; i < N_; ++i) {
        fwrite(&B1[i],sizeof(double),1,fp);
    }
    for (int i = 0; i < C_; ++i) {
        for (int j = 0; j < N_; ++j) {
            fwrite(&W2[i][j],sizeof(double),1,fp);
        }
    }
    for (int i = 0; i < C_; ++i) {
        fwrite(&B1[i],sizeof(double),1,fp);
    }
    fclose(fp);
}
//从文件"parameter.dat"文件中读取各参数
void data_read() {
    FILE* fp;
    fp = fopen("parameter.dat","rb");
    for (int i = 0; i < N_; ++i) {
        for (int j = 0; j < M_; ++j) {
            fread(&W1[i][j],sizeof(double),1,fp);
        }
    }
    for (int i = 0; i < N_; ++i) {
        fread(&B1[i],sizeof(double),1,fp);
    }
    for (int i = 0; i < C_; ++i) {
        for (int j = 0; j < N_; ++j) {
            fread(&W2[i][j],sizeof(double),1,fp);
        }
    }
    for (int i = 0; i < C_; ++i) {
        fread(&B2[i],sizeof(double),1,fp);
    }
    fclose(fp);
}