
#ifndef GOBANG_BOARD_H
#define GOBANG_BOARD_H

//宏定义区
#define childrenNum 150 // 每个节点的最大子节点数

// MCTS算法相关参数
#define C_UCT 1 // UCT中的参数C
#define E_times 400 // 每一步的评估次数
#define MCTS_times 400 // 每次评估的蒙特卡洛模拟次数

#define SIZE 15 // 棋盘大小

// 棋盘格子类型
#define B_EMPTY 0
#define B_BLACK 1
#define B_WHITE 2

//当前访问棋盘类型
#define REAL 1
#define VIRTUAL 0


//结构区
//节点结构
typedef struct node {
    //落子位置(x)
    int X;
    //落子位置(y)
    int Y;
    //价值
    double Q;
    //价值（由价值网络获取）
    double v;
    //访问次数
    int N;
    //节点的概率(由策略网络获得)
    double P;
    //节点的概率(由MCTS获取)
    double P_real;
    //此节点代表落子的颜色
    int type;
    //父节点
    struct node* father;
    //子节点
    struct node* children[childrenNum];
} Node;

//历史棋盘数据
typedef struct history_chessboard_data {
    //X代表当前棋手的历史落子，Y代表对方棋手的历史落子
    int X1[SIZE][SIZE];
    int Y1[SIZE][SIZE];
    int X2[SIZE][SIZE];
    int Y2[SIZE][SIZE];
    int X3[SIZE][SIZE];
    int Y3[SIZE][SIZE];
    int X4[SIZE][SIZE];
    int Y4[SIZE][SIZE];
    int X5[SIZE][SIZE];
    int Y5[SIZE][SIZE];
    int X6[SIZE][SIZE];
    int Y6[SIZE][SIZE];
    int X7[SIZE][SIZE];
    int Y7[SIZE][SIZE];
    int X8[SIZE][SIZE];
    int Y8[SIZE][SIZE];
    //当前落子人
    int type;
} HCD;

//全局变量区
//当前实际棋盘
extern int board_real[SIZE][SIZE];

//当前虚拟棋盘
extern int board_virtual[SIZE][SIZE];

//输赢
extern int win;

//相连棋子的首尾坐标
extern int start_x;
extern int start_y;
extern int end_x;
extern int end_y;

//神经网络输入
extern HCD NN_input;

//历史棋盘数据(实际)
extern int Board_History_Real[8][SIZE][SIZE];

//历史棋盘数据(虚拟)
extern int Board_History_Virtual[8][SIZE][SIZE];

//函数区
//重置棋盘
void resetBoard(int type);

//判断输赢
void game_terminate(int type);

// 初始化历史棋盘数据
void reset_HCD(int type);

// 记录历史棋盘数据
void write_chessboard_data(int D_type);

//数据转录
void data_trans(int B_type,int D_type);

//落子
void chess(int x,int y,int B_type,int D_type);

#endif //GOBANG_BOARD_H
