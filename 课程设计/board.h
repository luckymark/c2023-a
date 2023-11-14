
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
    int B1[SIZE][SIZE];
    int W1[SIZE][SIZE];
    int B2[SIZE][SIZE];
    int W2[SIZE][SIZE];
    int B3[SIZE][SIZE];
    int W3[SIZE][SIZE];
    int B4[SIZE][SIZE];
    int W4[SIZE][SIZE];
    int B5[SIZE][SIZE];
    int W5[SIZE][SIZE];
    int B6[SIZE][SIZE];
    int W6[SIZE][SIZE];
    int B7[SIZE][SIZE];
    int W7[SIZE][SIZE];
    int B8[SIZE][SIZE];
    int W8[SIZE][SIZE];
    //当前落子人（黑色为1，白色为2）
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

// 历史棋盘数据(实际)
extern HCD HCD_real;

//历史棋盘数据(模拟)
extern HCD HCD_virtual;

//函数区
//重置棋盘
void resetBoard(int type);

//判断输赢
void game_terminate(int type);

// 初始化历史棋盘数据
void reset_HCD(int type);

// 记录历史棋盘数据
void write_chessboard_data(int B_type, int D_type);

//直接对棋盘落子
void chess(int x,int y,int B_type,int D_type);

//根据节点对棋盘落子
void node_chess(Node* input,int D_type);

#endif //GOBANG_BOARD_H
