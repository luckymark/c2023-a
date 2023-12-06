
#ifndef C2023_CHALLENGE_MCTS_H
#define C2023_CHALLENGE_MCTS_H

#include <stdio.h>
#include "CNN.h"

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
// 创建根节点
void creatRoot(int x, int y, int type);

// 继承根节点
void inheritRoot();

// 评估和回传
void EstimateAndBack(std::string model_name = "",std::string model_save_name = "");

#endif //C2023_CHALLENGE_MCTS_H
