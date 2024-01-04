//
// Created by taiyehu on 2023/12/24.
//

#ifndef UNTITLED1_GAMETREE_H
#define UNTITLED1_GAMETREE_H
#include<iostream>
#include<vector>
#include<set>
#include<deque>
using namespace std;
class GameTree {
public:
    class Node{
    public:
        int value;//若为叶节点为估价，否则为alpha、beta值
        int depth;//深度
        Node *father;
        set<Node *> children;
        int cntX,cntY;//最后一步落子的x,y坐标
        int board[15][15]{};//当前棋局
        Node();
        Node(Node *node,int opX,int opY);
        bool isMaxNode();
        static int bEvaluate(string &s);
        static int wEvaluate(string &s);
        static string convert(int x);
        int check_win();
        void evaluate();
    };
    const int radius=2;//一个点向左向右各2格作为搜索范围
    const int maxDepth=9;//搜索时最大深度为5步
    Node *nodeRoot=new Node();//建树
    Node *nodeNext=NULL;//建树
    deque<Node *> openTable;
    deque<Node *> closedTable;
    vector<pair<int,int>> get_empty_pos(Node *node);
    int expandChildren(Node *node);
    static bool isCut(Node *node);
    static void updateNode(Node *node);
    void nextNode(Node *node);
    explicit GameTree(int mD,int R);
    explicit GameTree(int mD,int R,int (&board)[15][15]);
    int game();
    pair<int,int> get_next_pos();
    void show_next_pos();
};
#endif //UNTITLED1_GAMETREE_H
