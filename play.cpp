//
// Created by taiyehu on 2023/12/24.
//
#include<iostream>
#include"GameTree.h"
using namespace std;
pair<int,int> play(GameTree gt,int (&Board)[15][15]){
    //cout<<endl;
    int result=gt.game();
    if(result==2){
        return make_pair(-2,-2);
        //gt.show_board(false);
        //return;
    }
    if(result==1){
        return make_pair(-1,-1);
        //gt.show_board(false);
        //return;
    }
    //gt.show_next_pos();
    //gt.show_board(false);
    auto pos=gt.get_next_pos();
    if(pos.first!=-1 && pos.second!=-1) Board[pos.first][pos.second]=2;
    /*do{
        cin>>x>>y;
    }while(Board[x][y]!=0);*/
    //Board[x][y]=1;
    return pos;
}