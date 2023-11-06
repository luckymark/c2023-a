//
// Created by Administrator on 2023/10/26 0026.
//

#ifndef C2023_CHALLENGE_MCTS_H
#define C2023_CHALLENGE_MCTS_H

//每个节点的最大子节点数量
#define childrenNum 225
//节点
typedef struct node {
    //价值
    int value;
    //访问次数
    int S_times;
    //父节点
    struct node* father;
    //子节点
    struct node* children[childrenNum];
} Node;

//设置当前访问节点
void setTarget(Node* input);

//创建子节点
void createNode(int value, int S_times);

//判断是否是叶节点
int is_leaf();

//UCT算法搜索
void UCT(int n);

//反向传播更新访问次数
void back_times();

//反向传播更新价值
void back_value();

//输出target向量
Node* outputTarget();

#endif //C2023_CHALLENGE_MCTS_H
