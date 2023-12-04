
#ifndef C2023_CHALLENGE_MCTS_H
#define C2023_CHALLENGE_MCTS_H

#include "board.h"

//宏定义区

//结构区

//全局变量区
// 当前访问节点
extern Node* target;

// 策略分布
extern double policy[SIZE][SIZE];

// 价值分布
extern double value[SIZE][SIZE];

//外部可调用函数
// 设定访问节点
void setTarget(Node* input);

// 创建根节点
void creatRoot(int x, int y, int type);

// 释放内存
void freeTree(Node* input);

// 继承根节点
void inheritRoot();

// 为当前节点创建子节点
void createNode(int x, int y, double Q, double v, int N, double P, double P_real, int type);

// 判断当前节点是否是叶节点
int is_leaf();

// 根据UCT算法选择节点
void chooseNode();

// 判断当前节点是否为根节点
int is_root();

// 判断当前节点是否为下一步行动节点
int is_next_move();

// 返回根节点
Node* root();

// 回退至根节点
void back_to_root();

// 反向传播更新访问次数
void back_times();

// 根据模拟结果更新节点价值
void back_value();

// UCT算法搜索
void UCT();

// 展开节点
void expand();

// 评估和回传
void EstimateAndBack(char* model_name,char* opt_name);

#endif //C2023_CHALLENGE_MCTS_H
