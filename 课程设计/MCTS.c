/*
 * 蒙特卡洛树搜索代码
 * 代码运行逻辑仿照Java语言的面向对象编程逻辑
 * 每个node结构体视为一个对象
 * 使用setTarget(Node* input)函数设定当前程序访问的节点
 * 使用outputTarget()以在其它文件中访问target向量
 * 以上两个函数类似于"."运算符
 * 使用其它函数对当前对象进行操作
 */

#include <stdlib.h>
#include <math.h>
#include "MCTS.h"

//当前访问节点
Node* target;

//价值分布
double value[SIZE][SIZE];

//策略分布
double policy[SIZE][SIZE];

//无用の蜜汁小函数（返回当前根节点所有子节点的搜索次数综合）
double sum_N() {
    double sum = 0;
    for (int i = 0; i < childrenNum; ++i) {
        if (target->children[i] != NULL) {
            sum = (double) target->children[i]->N;
        }
    }
    return sum;
}

//设定访问节点
void setTarget(Node* input) {
    target = input;
}

//创建根节点
void creatRoot(int x,int y,int type) {
    target = (Node*) malloc(sizeof(Node));
    target -> X = x;
    target -> Y = y;
    target -> Q = 0;
    target -> v = 0;
    target -> N = 0;
    target -> P = 0;
    target -> P_real = 0;
    target -> type = type;
    target -> father = NULL;
    for (int j = 0; j < childrenNum; ++j) {
        target -> children[j] = NULL;
    }
}

//释放内存
void freeTree(Node* input) {

    if (input == NULL) return;

    for (int i = 0; i < childrenNum; i++) {
        if (input->children[i] != NULL) {
            freeTree(input->children[i]);
        }
    }
    free(input);
}

/*
 * 根据拓展、评估、回传阶段的结果选择最佳move作为下一步的根节点
 */
void inheritRoot() {
    int max_N = 0;
    for (int i = 0; i < childrenNum; ++i) {
        if (target->children[i]!=NULL) {
            max_N = max_N>target->children[i]->N ? max_N : target->children[i]->N;
        } else {
            break;
        }
    }
    int j;
    for (j = 0; j < childrenNum; ++j) {
        if (target->children[j]->N==max_N) {
            target = target->children[j];
            break;
        }
    }
    for (int i = 0; i < childrenNum; ++i) {
        if (i!=j) {
            free(target->father->children[i]);
            target->father->children[i] = NULL;
        }
    }
    free(target->father);
    target->father = NULL;
    chess(target->X,target->Y,target->type,REAL);
}

//为当前节点创建一个子节点
void createNode(int x,int y,double Q,double v,int N,double P,double P_real,int type) {
    for (int i = 0; i < childrenNum; ++i) {
        if (target->children[i] == NULL) {
            Node* newNode = (Node*) malloc(sizeof(Node));
            newNode -> X = x;
            newNode -> Y = y;
            newNode -> Q = Q;
            newNode -> v = v;
            newNode -> N = N;
            newNode -> P = P;
            newNode -> P_real = P_real;
            newNode -> type = type;
            newNode -> father = target;
            for (int j = 0; j < childrenNum; ++j) {
                newNode -> children[j] = NULL;
            }
            target -> children[i] = newNode;
            break;
        }
    }
}

//判断当前节点是否是叶节点
int is_leaf() {
    for (int i = 0; i < childrenNum; ++i) {
        if (target->children[i] != NULL) {
            return 0;
        }
    }
    return 1;
}

//根据UCT算法选择节点
void chooseNode() {
    double max;
    for (int i = 0; i < childrenNum; ++i) {
        if (target -> children[i] != NULL) {
            max = max > target->children[i]->P_real ? max : target->children[i]->P_real;
        } else {
            break;
        }
    }
    for (int j = 0; j < childrenNum; ++j) {
        if (target->children[j] != NULL) {
            if (target->children[j]->P_real == max) {
                target = target->children[j];
            }
        } else {
            break;
        }
    }
}

//判断当前节点是否为根节点
int is_root() {
    if (target->father == NULL) {
        return 1;
    } else {
        return 0;
    }
}

//判断当前节点是否为下一步行动
int is_next_move() {
    if (target->father->father == NULL) {
        return 1;
    } else {
        return 0;
    }
}

//返回根节点
Node* root() {
    Node* now = target;
    while (!is_root()) {
        target = target -> father;
    }
    Node* result = target;
    target = now;
    return result;
}

//回退至根节点
void back_to_root() {
    while (!is_root()) {
        target = target->father;
    }
}

/*
 * 根据模拟所得的价值来更新下一步行动的价值
 */
void back_value() {
    Node* now = target;
    double v = target->v;
    while (!is_next_move()) {
         target = target -> father;
    }
    target -> Q = (v+((double)target->N-1)*target->Q)/(double)target->N;
    target = now;
}

/*
 * 最大置信上界算法搜索(Upper Confidence Bound Apply to Tree, UCT)
 * 一次只执行一步
 */
void UCT() {
    for (int i = 0; i < childrenNum; ++i) {
        if(target -> children[i] != NULL) {
            target -> children[i] -> P_real = C_UCT * target->children[i]->P * ( sqrt((double)root()->N)/(1+(double)target->children[i]->N) );
            target -> children[i] -> P_real += target -> children[i] -> Q;
        } else {
            break;
        }
    }
    chooseNode();
}

//神经网络接口（待实现）
void NeutralNetwork() {

}

//展开
void expand() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (policy[i][j] != 0) {
                createNode(j,i,0,value[i][j],0,policy[i][j],0,(target->type==B_BLACK?B_WHITE:B_BLACK));
            }
        }
    }
}

//评估与回传
void EstimateAndBack() {
    data_trans((target->type == B_BLACK ? B_WHITE : B_BLACK),REAL);
    /*
     * 此处应根据当前实际棋盘状态进行一次神经网络评估
     */
    //第一次展开，生成所有可能的move;
    expand();
    for (int i = 0; i < E_times; ++i) {
        //重置虚拟棋盘与虚拟历史落子数据
        resetBoard(VIRTUAL);
        reset_HCD(VIRTUAL);
        //选择一个move
        back_to_root();
        target -> N++;
        UCT();
        target->N++;
        //存储下一步落子颜色
        int type = target -> type;
        //落子
        chess(target->X,target->Y,target->type,VIRTUAL);
        data_trans((target->type == B_BLACK ? B_WHITE : B_BLACK),VIRTUAL);
        //开始评估
        for (int j = 0; j < MCTS_times; ++j) {
            /*
             * 神经网络评估
             */
            //拓展
            expand();
            //选择
            UCT();
            //落子
            chess(target->X,target->Y,target->type,VIRTUAL);
            data_trans((target->type == B_BLACK ? B_WHITE : B_BLACK),VIRTUAL);
            //判断游戏是否到达终局
            game_terminate(VIRTUAL);
            if (win != 0) {
                if (win==3) {
                    target->v = 0;
                } else {
                    target->v = win == type ? 1 : -1;
                }
                back_value();
                break;
            }
            //回传
            back_value();
        }
        //释放内存，清除用无节点
        while (!is_next_move()) {
            target = target->father;
        }
        for (int j = 0; j < childrenNum; ++j) {
            if (target->children[j] != NULL) {
                freeTree(target->children[j]);
                target->children[j] = NULL;
            }
        }
    }
    //评估结束，返回根节点
    back_to_root();
    //生成先验落子概率与先验价值向量、落子概率与价值向量
    int count = 0;
    for (int i = 0; i < childrenNum; ++i) {
        if (target->children[i] != NULL) {
            count++;
        }
    }
    double* P_CNN = (double*) malloc(count* sizeof(double ));
    double* P_MCTS = (double*) malloc(count* sizeof(double ));
    double* V_CNN = (double*) malloc(count*sizeof(double ));
    double* V_MCTS = (double*) malloc(count*sizeof(double ));
    for (int i = 0; i < count; ++i) {
        P_CNN[i] = target->children[i]->P;
        V_CNN[i] = target->children[i]->v;
        P_MCTS[i] = ((double)target->children[i]->N)/sum_N();
        V_MCTS[i] = target->children[i]->Q;
    }
    /*
    * 更新神经网络参数
    */
}