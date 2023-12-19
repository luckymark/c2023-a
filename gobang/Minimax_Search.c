#include <stdlib.h>
#include <stdbool.h>
#include "Evaluate.h"
#include "Minimax_Search.h"
#include "Inspire_Search.h"
//缩小落子范围
bool Is_drop(int x,int y,int map[][15])
{
    if((x<2 || x>12 || y<2 || y>12) || (map[x-2][y]==0 && map[x-1][y]==0 && map[x+1][y]==0 && map[x+2][y]==0
    && map[x][y-2]==0 && map[x][y-1]==0 && map[x][y+1]==0 && map[x][y+2]==0
    && map[x-2][y-2]==0 && map[x-1][y-1]==0 && map[x+1][y+1]==0 && map[x+2][y+2]==0
    && map[x-2][y+2]==0 && map[x-1][y+1]==0 && map[x+1][y-1]==0 && map[x+2][y-2]==0)
    ||(map[x][y]!=0))
    {
        return false;
    }
    else
    {
        return true;
    }
}
//考察AI落子的反馈
Feedback* AI_drop(int i,int j,int map[][15])
{
    Feedback* result = (Feedback*) malloc(sizeof(Feedback));
    map[i][j]=-1;
    result->score = Evaluate(map);
    map[i][j]=0;
    return result;
}
//创建根节点
Root* Create_Root(int map[][15])
{
    //开辟根节点空间
    Root* root = (Root*) malloc(sizeof(Root));
    //设置根节点深度和Max类别
    root->depth=0;
    root->IsMax=1;
    root->score=-100000;
    root->pre=-100000;
    //调用启发式函数生成搜索顺序表
    pos* pt = Search_list_white(map);
    for(int k=0;pt[k].x!=0 || pt[k].y!=0;k++)
    {
        int i = pt[k].x;
        int j = pt[k].y;
        map[i][j]=-1;
        int feedback = Create_children(root->IsMax,root->depth,root->pre,map);
        if(feedback>=root->score)
        {
            root->score=feedback;
            root->pre=feedback;
            root->x=i;
            root->y=j;
        }
        map[i][j]=0;
    }
    return root;
}
//生成子节点
int Create_children(bool Is_Father_Max,int Father_depth,int pre,int map[][15])
{
    //开辟节点空间
    Node *node = (Node *) malloc(sizeof(Node));
    //判断是否为Max节点
    if (Is_Father_Max)
    {
        node->IsMax = 0;
    }
    else
    {
        node->IsMax = 1;
    }
    //初始化α和β的值
    node->alpha = -100000;
    node->beta = 100000;
    //若为Max节点
    if (node->IsMax)
    {
        //调用启发式函数生成搜索顺序表
        pos *pt = Search_list_white(map);
        //判断是否为叶节点
        node->depth = Father_depth + 1;
        //若为叶节点
        if (node->depth == 1)
        {
            node->score = -100000;
            for (int k = 0; pt[k].x != 0 || pt[k].y != 0; k++)
            {
                int i = pt[k].x;
                int j = pt[k].y;
                map[i][j] = -1;
                int feedback = Evaluate(map);
                map[i][j] = 0;
                if (feedback > pre)
                {
                    int score = 100000;
                    free(node);
                    return score;
                }
                node->score = (feedback >= node->score ? feedback : node->score);
            }
        }
        //若不是叶节点
        else
        {
            node->pre = -100000;
            for (int k = 0; pt[k].x != 0 || pt[k].y != 0; k++)
            {
                int i = pt[k].x;
                int j = pt[k].y;
                map[i][j] = -1;
                int feedback = Create_children(node->IsMax, node->depth, node->pre, map);
                map[i][j] = 0;
                node->pre = (feedback > node->pre ? feedback : node->pre);
                if (feedback > pre)
                {
                    int score = 100000;
                    free(node);
                    return score;
                }
                node->alpha = (feedback >= node->alpha ? feedback : node->alpha);
            }
            node->score = node->alpha;
        }
    }
    //若为Min节点
    else
    {
        //调用启发式函数生成搜索顺序表
        pos *pt = Search_list_black(map);
        //判断是否为叶节点
        node->depth = Father_depth + 1;
        //若为叶节点
        if (node->depth == 1)
        {
            node->score = 100000;
            for (int k = 0; pt[k].x != 0 || pt[k].y != 0; k++)
            {
                int i = pt[k].x;
                int j = pt[k].y;
                map[i][j] = 1;
                int feedback = Evaluate(map);
                map[i][j] = 0;
                if (feedback < pre)
                {
                    int score = -100000;
                    free(node);
                    return score;
                }
                node->score = (feedback <= node->score ? feedback : node->score);
            }
        }
        //若不是叶节点
        else
        {
            node->pre = 100000;
            for (int k = 0; pt[k].x != 0 || pt[k].y != 0; k++)
            {
                int i = pt[k].x;
                int j = pt[k].y;
                map[i][j] = 1;
                int feedback = Create_children(node->IsMax, node->depth, node->pre, map);
                map[i][j] = 0;
                node->pre = (feedback < node->pre ? feedback : node->pre);
                if (feedback < pre)
                {
                    int score = -100000;
                    free(node);
                    return score;
                }
                node->beta = (feedback <= node->beta ? feedback : node->beta);
            }
            node->score = node->beta;
        }
    }
    int score = node->score;
    free(node);
    return score;
}
/*
    else
    {
        pos* pt = Search_list_black(map);
    }
    //判断是否为叶节点
    node->depth=Father_depth+1;
    if(node->depth==1)
    {
        if(node->IsMax)
        {
            node->score=-100000;
            for(int k=0;pt[k].x!=0 || pt[k].y!=0;k++)
            {
                int i = pt[k].x;
                int j = pt[k].y;
                map[i][j]=-1;
                int feedback = Evaluate(map);
                map[i][j]=0;
                if(feedback>pre)
                {
                    int score=100000;
                    free(node);
                    return score;
                }
                node->score = (feedback>=node->score? feedback:node->score);
            }
        }
        else
        {
            node->score=100000;
            for(int k=0;pt[k].x!=0 || pt[k].y!=0;k++)
            {
                int i = pt[k].x;
                int j = pt[k].y;
                map[i][j]=1;
                int feedback = Evaluate(map);
                map[i][j]=0;
                if(feedback<pre)
                {
                    int score=-100000;
                    free(node);
                    return score;
                }
                node->score = (feedback<=node->score? feedback:node->score);
            }
        }
        int score=node->score;
        free(node);
        return score;
    }
    //若为Max节点，不断更新其α值，最后返回一个得分
    if(node->IsMax)
    {
        node->pre=-100000;
        for(int k=0;pt[k].x!=0 || pt[k].y!=0;k++)
        {
            int i = pt[k].x;
            int j = pt[k].y;
            map[i][j]=-1;
            int feedback = Create_children(node->IsMax,node->depth,node->pre,map);
            map[i][j]=0;
            node->pre = (feedback>node->pre? feedback:node->pre);
            if(feedback>pre)
            {
                int score=100000;
                free(node);
                return score;
            }
            node->alpha = (feedback>=node->alpha? feedback:node->alpha);
        }
        node->score=node->alpha;
    }
    //若为Min节点，不断更新其β值，最后返回一个得分
    else
    {
        node->pre=100000;
        for(int k=0;pt[k].x!=0 || pt[k].y!=0;k++)
        {
            int i = pt[k].x;
            int j = pt[k].y;
            map[i][j]=1;
            int feedback = Create_children(node->IsMax,node->depth,node->pre,map);
            map[i][j]=0;
            node->pre = (feedback<node->pre? feedback:node->pre);
            if(feedback<pre)
            {
                int score=-100000;
                free(node);
                return score;
            }
            node->beta = (feedback<=node->beta? feedback:node->beta);
        }
        node->score=node->beta;
    }
    int score=node->score;
    free(node);
    return score;
}*/
//为当前MAX节点赋值
/*
Node* Give_Max_Value(int map[][15])
{
    Node* MAX = (Node*) malloc(sizeof(Node));
    MAX->beta=-100000;
    int alpha;
    int pre_alpha=-100000;
    pos* pt = Search_list(map);
    for(int k=0;pt[k].x!=0 || pt[k].y!=0;k++)
    {
        int i=pt[k].x;
        int j=pt[k].y;
        map[i][j]=-1;
        alpha = Search(pre_alpha,map);
        pre_alpha=(alpha>=pre_alpha? alpha:pre_alpha);
        map[i][j]=0;
        if(alpha>=MAX->beta)
        {
            MAX->beta=alpha;
        }
    }
    return MAX;
}
//遍历子节点
int Search(int pre_alpha,int map[][15])
{
    int score;
    int alpha=100000;
    pos* pt = Search_list(map);
    for(int k=0;pt[k].x!=0 || pt[k].y!=0;k++)
    {
        int i=pt[k].x;
        int j=pt[k].y;
        map[i][j]=1;
        score=Evaluate(map);
        map[i][j]=0;
        if(score<pre_alpha)
        {
            return -100000;
        }
        alpha=(score<=alpha? score:alpha);
    }
    return alpha;
}*/
//构建博弈树