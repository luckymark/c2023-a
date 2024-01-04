//
// Created by taiyehu on 2023/12/25.
//
#include "GameTree.h"
void test(int (&Board)[15][15]){
    int flag=1;
    int x,y;
    while(1){
        GameTree gt=GameTree(9,2,Board);
        if(flag==1){
            gt.game();
            Board[7][7]=2;
            flag=0;
        }
        else gt.game();
        gt.show_next_pos();
        auto pos=gt.get_next_pos();
        if(pos.first!=-1 && pos.second!=-1) Board[pos.first][pos.second]=2;
        do{
            cin>>x>>y;
        }while(Board[x][y]!=0);
        Board[x][y]=1;
    }
}
