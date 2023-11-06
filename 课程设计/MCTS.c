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
#include <float.h>
#include <math.h>
#include "MCTS.h"

//UCT算法超参数
#define c 0.5

//当前访问节点
Node* target;

//设定访问节点
void setTarget(Node* input) {
    target = input;
}

//为当前节点创建一个子节点，可自主设定价值与访问次数
void createNode(int value,int S_times) {
    for (int i = 0; i < childrenNum; ++i) {
        if (target->children[i] == NULL) {
            Node* newNode = (Node*) malloc(sizeof(Node));
            newNode -> father = target;
            newNode -> value = value;
            newNode -> S_times = S_times;
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

//根据UCT算法结果返回UCT算法计算值最大的子节点的索引
int max_mark(double input[childrenNum]) {
    double max = 0;
    for (int i = 0; i < childrenNum; ++i) {
        max = max > input[i] ? max : input[i];
    }
    for (int i = 0; i < childrenNum; ++i) {
        if (max == input[i]) {
            return i;
        }
    }
    return 0;
}

//判断当前节点是否为根节点
int is_root() {
    if (target->father == NULL) {
        return 1;
    } else {
        return 0;
    }
}

//反向传播更新访问次数
void back_times() {
    while (!is_root()) {
        target->S_times++;
        target = target->father;
    }
}

//反向传播更新价值
void back_value() {
    while (!is_root()) {
        Node* now = target;
        target = target->father;
        target -> value += now->value;
    }
}

/*
 * 最大置信上界算法搜索(Upper Confidence Bound Apply to Tree, UCT)
 * 每一轮搜索从当前节点开始，向下搜索n层(若n=-1，则搜索至叶节点结束)
 * 搜索开始时先反向传播以更新当前节点以前节点的访问次数
 * 搜索时每搜索至一个节点时增加该节点的访问次数
 * 采用以上更新方式以避免初次开始搜索时根节点访问次数为0导致计算错误
 */
void UCT(int n) {
    //存储UCT算法的计算结果
    double result[childrenNum];
    if (n==-1) {
        //初次更新访问次数
        if (is_root()) {
            target->S_times++;
        } else {
            //反向传播更新访问次数
            Node * now = target;
            back_times();
            target = now;
        }
        //搜索至叶节点结束
        while (!is_leaf()) {
            //每次初始化result数组
            for (int i = 0; i < childrenNum; ++i) {
                result[i] = 0;
            }
            //UCT算法计算
            for (int i = 0; i < childrenNum; ++i) {
                if (target->children[i] != NULL) {
                    //若访问次数为0，则使其值为极大值，代表必定访问
                    if (target->children[i]->S_times == 0) {
                        result[i] = DBL_MAX;
                    } else {
                        result[i] = (double)target->children[i]->value/target->children[i]->S_times+c* sqrt((double) log((double)target->S_times)/target->children[i]->S_times);
                    }
                } else {
                    break;
                }
            }
            setTarget(target->children[max_mark(result)]);
            //正向更新访问次数
            target->S_times++;
        }
    } else {
        //初次更新访问次数
        if (is_root()) {
            target->S_times++;
        } else {
            //反向传播更新访问次数
            Node * now = target;
            back_times();
            target = now;
        }
        //向下搜索n层
        for (int i = 0; i < n; ++i) {
            //每次初始化result数组
            for (int j = 0; j < childrenNum; ++j) {
                result[j] = 0;
            }
            //UCT算法计算
            for (int j = 0; j < childrenNum; ++j) {
                if (target->children[j] != NULL) {
                    //若访问次数为0，则使其值为极大值，代表必定访问
                    if (target->children[j]->S_times == 0) {
                        result[j] = DBL_MAX;
                    } else {
                        result[j] = (double)target->children[j]->value / target->children[j]->S_times + c * sqrt((double) log((double)target->S_times) / target->children[j]->S_times);
                    }
                } else {
                    break;
                }
            }
            setTarget(target->children[max_mark(result)]);
            //正向更新访问次数
            target->S_times++;
        }
    }
}

//输出target向量以供其它文件访问
Node* outputTarget() {
    return target;
}




