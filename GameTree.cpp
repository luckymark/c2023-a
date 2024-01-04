//
// Created by taiyehu on 2023/12/24.
//
#include <iostream>
#include <set>
#include <cstring>
#include <deque>
#include <vector>
#include "GameTree.h"
using namespace std;
        //构建根节点
        GameTree::Node::Node(){
            father=nullptr;
            children.clear();
            value = INT_MIN;
            depth=cntX=cntY=0;
            memset(board,0,sizeof(0));
        }
        //构建叶节点
        GameTree::Node::Node(Node *node,int opX,int opY){
            depth=node->depth+1;
            value= isMaxNode() ? INT_MIN : INT_MAX;//赋初值
            father=node;
            children.clear();
            cntX=opX;
            cntY=opY;
            memcpy(board,node->board,sizeof(board));
            board[cntX][cntY]=(depth%2==0?1:2);//1白2黑
        }
        //判断当前是否为max节点
        bool GameTree::Node::isMaxNode(){
            return (depth%2==0);
        }
        //对黑棋估价
        int GameTree::Node::bEvaluate(string &s){
            string patterns[31]={
                    "20000","02000","00200","00020","00002",
                    "22000","02200","00220","00022","20200","02020","00202","20020","02002","20002",
                    "22200","02220","00222","22020","02202","20220","02022","22002","20022","20202",
                    "22220","22022","20222","22202","02222",
                    "22222"
            };
            int scores[31]={
                    1,1,1,1,1,
                    10,10,10,10,10,10,10,10,10,10,
                    100,100,100,100,100,100,100,100,100,100,
                    10000,10000,10000,10000,10000,
                    1000000
            };
            for(int i=0;i<31;i++){
                if(s==patterns[i]) return scores[i];
            }
            return 0;
        }
        //对白棋估价
        int GameTree::Node::wEvaluate(string &s){
            string patterns[31]={
                    "10000","01000","00100","00010","00001",
                    "11000","01100","00110","00011","10100","01010","00101","10010","01001","10001",
                    "11100","01110","00111","11010","01101","10110","01011","11001","10011","10101",
                    "11110","11011","10111","11101","01111",
                    "11111"
            };
            int scores[31]={
                    1,1,1,1,1,
                    10,10,10,10,10,10,10,10,10,10,
                    1000,2000,1000,1000,1000,1000,1000,1000,1000,1000,
                    100000,100000,100000,100000,100000,
                    10000000
                    /*1,1,1,1,1,
                    10,10,10,10,10,10,10,10,10,10,
                    100,100,100,100,100,100,100,100,100,100,
                    10000,10000,10000,10000,10000,
                    1000000*/
            };
            for(int i=0;i<31;i++){
                if(s==patterns[i]) return scores[i];
            }
            return 0;
        }
        //将数字转换为字符
        string GameTree::Node::convert(int x){
            if(x==0) return "0";
            if(x==1) return "1";
            else return "2";
        }
        //判断是否结束
        int GameTree::Node::check_win(){
            for(int i=0;i<15;i++)
                for(int j=0;j<15;j++){
                    if(j+4<15){
                        string s;
                        for(int k=0;k<5;k++) s+=convert(board[i][j+k]);
                        if(s=="11111") return '1';
                        if(s=="22222") return '2';
                    }
                    if(i+4<15){
                        string s;
                        for(int k=0;k<5;k++) s+=convert(board[i+k][j]);
                        if(s=="11111") return '1';
                        if(s=="22222") return '2';
                    }
                    if(i+4<15 && j+4<15){
                        string s;
                        for(int k=0;k<5;k++) s+=convert(board[i+k][j+k]);
                        if(s=="11111") return '1';
                        if(s=="22222") return '2';
                    }
                    if(i+4<15 && j-4>=0){
                        string s;
                        for(int k=0;k<5;k++) s+=convert(board[i+k][j-k]);
                        if(s=="11111") return '1';
                        if(s=="22222") return '2';
                    }
                }
            return 0;
        }
        //对局面进行评估
        void GameTree::Node::evaluate(){
            value=0;
            for(int i=0;i<15;i++)
                for(int j=0;j<15;j++){
                    if(j+4<15){
                        string s;
                        for(int k=0;k<5;k++) s+=convert(board[i][j+k]);
                        value+=(bEvaluate(s)-wEvaluate(s));
                    }
                    if(i+4<15){
                        string s;
                        for(int k=0;k<5;k++) s+=convert(board[i+k][j]);
                        value+=(bEvaluate(s)-wEvaluate(s));
                    }
                    if(j+4<15 && i+4<15){
                        string s;
                        for(int k=0;k<5;k++) s+=convert(board[i+k][j+k]);
                        value+=(bEvaluate(s)-wEvaluate(s));
                    }
                    if(i+4<15 && j-4>=0){
                        string s;
                        for(int k=0;k<5;k++) s+=convert(board[i+k][j-k]);
                        value+=(bEvaluate(s)-wEvaluate(s));
                    }
                }
        }
        //输出当前状态
        /*void GameTree::Node::print_info(){
            cout<<this<<"depth= "<<depth<<"value= "<<value<<"father= "<<father<<"children=(";
            for(auto child:children) cout<<child<<",";
            cout<<")"<<endl;
            for(auto &i:board){
                cout<<"    ";
                for(auto j:i){
                    if(j=='1') cout<<"B";
                    if(j=='2') cout<<"W";
                    if(j=='0') cout<<" ";
                }
                cout<<endl;
            }
        }*/


    //获取当前棋局可作为子节点的格子
    vector<pair<int,int>> GameTree::get_empty_pos(Node *node){//找到空的可以落子的格点
        bool isEmpty=true,newBoard[15][15];
        memset(newBoard,false,sizeof(newBoard));
        for(int i=0;i<15;i++){
            for(int j=0;j<15;j++){
                if(node->board[i][j]==0) continue;
                isEmpty=false;
                int x1=max(i-radius,0),x2=min(i+radius,14),y1=max(j-radius,0),y2=min(j+radius,14);
                for(int x=x1;x<=x2;x++)
                    for(int y=y1;y<=y2;y++)
                        if(node->board[x][y]==0) newBoard[x][y]=true;
            }
        }
        vector<pair<int,int>> emptyPos;
        if(isEmpty) emptyPos.push_back(make_pair(7,7));
        else {
            for (int i = 0; i <= 14; i++)
                for (int j = 0; j <= 14; j++)
                    if (newBoard[i][j]) emptyPos.push_back(make_pair(i, j));
        }
        return emptyPos;
    }
    //向下扩张树
    int GameTree::expandChildren(Node *node){
        vector<pair<int,int>> emptyPos=get_empty_pos(node);
        if(emptyPos.size()==0) return 0;
        for(auto pos:emptyPos){
            Node *n=new GameTree::Node(node,pos.first,pos.second);
            node->children.insert(n);
            openTable.push_front(n);
        }
        return emptyPos.size();
    }
    //alpha-beta剪枝
    bool GameTree::isCut(Node *node){
        if(node==NULL || node->father==NULL) return false;
        if(node->isMaxNode() && node->value > node->father->value) return true;
        if(!node->isMaxNode() && node->value < node->father->value) return true;
        return isCut(node->father);
    }
    //更新节点的值
    void GameTree::updateNode(Node *node){
        if(node==NULL) return;
        if(node->children.empty()){
            updateNode(node->father);
            return;
        }
        if(node->isMaxNode()){
            int tmp=INT_MIN;
            for(auto child:node->children){
                if(child->value!=INT_MAX) tmp=max(tmp,child->value);
            }
            if(tmp > node->value){
                node->value=tmp;
                updateNode(node->father);
            }
        }
        else{
            int tmp=INT_MAX;
            for(auto child:node->children){
                if(child->value!=INT_MIN) tmp=min(tmp,child->value);
            }
            if(tmp < node->value){
                node->value=tmp;
                updateNode(node->father);
            }
        }
    }
    //选择下一步节点
    void GameTree::nextNode(Node *node){
        nodeNext=*node->children.begin();
        for(Node *child:node->children)
            if(child->value>=nodeNext->value) nodeNext=child;
    }

    //GameTree()=default;
    GameTree::GameTree(int mD,int R): maxDepth(mD),radius(R){}
    GameTree::GameTree(int mD,int R,int (&board)[15][15]): maxDepth(mD),radius(R){
        memcpy(nodeRoot->board,board,sizeof(board));
    }
    int GameTree::game(){
        if(nodeRoot->check_win()!=0) return nodeRoot->check_win()=='1'?1:2;
        openTable.push_back(nodeRoot);
        while(!openTable.empty()){
            Node *node=openTable.front();
            openTable.pop_front();
            closedTable.push_back(node);
            if(isCut(node->father)) continue;
            if(node->depth<maxDepth) {
                int tmp = expandChildren(node);
                if (tmp) continue;
            }
            node->evaluate();
            updateNode(node);
        }
        nextNode(nodeRoot);
        return 0;
    }

    pair<int,int> GameTree::get_next_pos(){
        if(nodeNext==nullptr) return pair<int,int>(-1,-1);
        return pair<int,int>(nodeNext->cntX,nodeNext->cntY);
    }

    void GameTree::show_next_pos(){
        if(nodeNext==nullptr) cout<<"(255,255)"<<endl;
        else cout<<"("<<nodeNext->cntX<<","<<nodeNext->cntY<<")"<<endl;
    }

    /*void GameTree::show_board(bool reverse) {
        if (nodeNext == nullptr) nodeNext = nodeRoot;
        int row = 0;
        cout << "   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4" << endl;
        for (int i = 0; i < 15; i++) {
            if (row < 10) cout << " ";
            cout << row++ << " ";
            for (int j = 0; j < 15; j++) {
                if (j != 0) cout << " ";
                if (nodeNext->board[i][j] == '2') {
                    if(reverse) cout << "B";
                    else cout << "W";
                    continue;
                }
                if (nodeNext->board[i][j] == '1') {
                    if (reverse) cout << "W";
                    else cout << "B";
                    continue;
                }
                if (i == 0 && j == 0) {
                    cout << " ";
                    continue;
                }
                if (i == 0 && j == 14) {
                    cout << " ";
                    continue;
                }
                if (i == 14 && j == 0) {
                    cout << " ";
                    continue;
                }
                if (i == 14 && j == 14) {
                    cout << " ";
                    continue;
                }
                if (i == 0) {
                    cout << " ";
                    continue;
                }
                if (i == 14) {
                    cout << " ";
                    continue;
                }
                if (j == 0) {
                    cout << " ";
                    continue;
                }
                if (j == 14) {
                    cout << " ";
                    continue;
                }
                cout << " ";
            }
            cout << endl;
        }
        cout << endl;
        nodeNext->print_info();
        cout<<endl;
    }*/