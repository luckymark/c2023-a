#include <conio.h>
#include "gamefunction.h"

//请生成可执行文件，用Windows的终端运行，勿用Clion的内置终端运行。
//If it's unrecognizable above,please change the code format to GBK.

int main(){
    point player={5,5};
    point target[]={4,1,5,1,6,1};
    int targets = 3;
    char walls[10][10]={{0,1,1,1,1,1,1,1,0,0},
                        {0,1,0,0,0,0,0,1,0,0},
                        {0,1,0,0,0,1,1,1,1,0},
                        {1,1,1,0,0,0,0,0,1,0},
                        {1,0,0,0,1,2,1,0,1,0},
                        {1,0,2,2,1,0,0,0,1,0},
                        {1,0,0,0,1,1,1,1,1,0},
                        {1,1,1,1,1,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
    };
    while (allBack(&walls,target,targets)!=1){
        setmap(&walls,&player,target,targets);
        int input = getch();
        switch(input){
            case 'W': playermove(&walls,&player,Up);break;
            case 'w': playermove(&walls,&player,Up);break;
            case 'S': playermove(&walls,&player,Down);break;
            case 's': playermove(&walls,&player,Down);break;
            case 'A': playermove(&walls,&player,Left);break;
            case 'a': playermove(&walls,&player,Left);break;
            case 'D': playermove(&walls,&player,Right);break;
            case 'd': playermove(&walls,&player,Right);break;
            default: break;
        }
    }
    setmap(&walls,&player,target,targets);
    gameover();
    return 0;
}