#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "gameFunction.h"

//请生成可执行文件，用Windows的终端运行，勿用Clion的内置终端运行。
//If it's unrecognizable above,please change the code format to GBK.

int main(){
    int decision;
    printf("Select one map to play.\nOptions:1 2 3\n");
    scanf("%d",&decision);
    char mapname[10]={"Error"};
    switch (decision) {
        case 1:{char temp[10] = "map1.txt";strcpy(mapname,temp);};break;
        case 2:{char temp[10] = "map2.txt";strcpy(mapname,temp);};break;
        case 3:{char temp[10] = "map3.txt";strcpy(mapname,temp);};break;
        default:break;
    }
    system("cls");

    FILE *map = fopen(mapname, "r+");
    if (map) {
        point player;
        for (int i; (i = fgetc(map)) != ':';);
        fscanf(map, "%d,%d", &player.x, &player.y);

        int targets;
        for (char i; (i = fgetc(map)) != ':';);
        fscanf(map, "%d", &targets);

        point target[targets];
        for (char i; (i = fgetc(map)) != ':';);
        for (int count = 0; count < targets * 2;) {
            char i = fgetc(map);
            if (i == ',') {
                continue;
            }
            count++;
            if (count % 2) {
                fseek(map, -1, SEEK_CUR);
                fscanf(map, "%1d", &target[(count + 1) / 2 - 1].x);
            } else {
                fseek(map, -1, SEEK_CUR);
                fscanf(map, "%1d", &target[count / 2 - 1].y);
            }
        }

        char walls[10][10];

        for (char i; (i = fgetc(map)) != ':';);
        fgetc(map);
        for (int i = 0,j = 0,c; (c = fgetc(map)) != '.';) {
            if (c == '\n') {
                i++;
                j = 0;
            } else {
                fseek(map, -1, SEEK_CUR);
                fscanf(map, "%1d", &walls[i][j]);
                j++;
            }
        }

        int step = 0;
        while (allBack(walls,target,targets)!=1){
            setmap(walls,&player,target,targets);
            int input = getch();
            switch(input){
                case 'W': playermove(walls,&player,Up);break;
                case 'w': playermove(walls,&player,Up);break;
                case 'S': playermove(walls,&player,Down);break;
                case 's': playermove(walls,&player,Down);break;
                case 'A': playermove(walls,&player,Left);break;
                case 'a': playermove(walls,&player,Left);break;
                case 'D': playermove(walls,&player,Right);break;
                case 'd': playermove(walls,&player,Right);break;
                default: break;
            }
            step++;
        }

        setmap(walls,&player,target,targets);
        gameover(step);

        for (int i = 0; (i = fgetc(map)) != ':';);
        int l_step = ftell(map);
        fseek(map,0,SEEK_CUR);
        for(int i = 0; i < (SEEK_END-l_step); i++) {
            fprintf(map," ");
        }
        fseek(map,0,l_step);
        fprintf(map,"%d",step);

        fclose(map);
    } else {
        printf("Fail To Open The Map.");
        getch();
    }

    //version2 target[] failed.
    /*point player;
    int targets;
    point *target = NULL;//not sure to be enough space for the list.
    char (*walls)[10]=NULL;

    load("map1.txt",&player,&targets,target,walls);*/

    //version 1
    /*point player={5,5};
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
    };*/

    return 0;
}