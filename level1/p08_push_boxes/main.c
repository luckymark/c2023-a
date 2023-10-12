#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int main(){
    char list[11][11]={
            {'#','#','#','#','#','#','#','#','#','#','#'},
            {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
            {'#',' ',' ',' ',' ',' ',' ','#',' ','*','#'},
            {'#',' ',' ',' ','*','#','*',' ','#',' ','#'},
            {'#','#',' ','#',' ',' ','#',' ','@',' ','#'},
            {'#',' ',' ',' ',' ',' ',' ','@',' ',' ','#'},
            {'#',' ','@',' ',' ',' ','@',' ',' ',' ','#'},
            {'#',' ','#','@',' ',' ',' ',' ',' ',' ','#'},
            {'#',' ',' ',' ','#',' ','#',' ',' ',' ','#'},
            {'#','*',' ',' ',' ',' ',' ',' ','#','*','#'},
            {'#','#','#','#','#','#','#','#','#','#','#'}
    };
    int i,j,f=0,step=0;
    int ip=1,jp=1;
    char ch;
    char name='P';
    while(f<5) {
        system("cls");
        for (i = 0; i < 11; i++) {
            for (j = 0; j < 11; j++) {
                if (i==ip && j==jp) {
                    printf("%c", name);
                }
                else
                {
                    printf("%c", list[i][j]);
                }
                printf(" ");
            }
            printf("\n");
        }
        ch=getch();
        if ((ch=='w') && ( (list[ip-1][jp]!='#') && (list[ip-1][jp]!='@')))
        {
            ip--;
            step++;
        }
        else if ((ch=='s') &&  ( (list[ip+1][jp]!='#') && (list[ip+1][jp]!='@')))
        {
            ip++;
            step++;
        }
        else if ((ch=='a') &&  ( (list[ip][jp-1]!='#') && (list[ip][jp-1]!='@')))
        {
            jp--;
            step++;
        }
        else if ((ch=='d') &&  ( (list[ip][jp+1]!='#') && (list[ip][jp+1]!='@')))
        {
            jp++;
            step++;
        }
        else if((ch=='w') && (list[ip-1][jp]=='@') && (list[ip-2][jp]!='#') && (list[ip-2][jp]!='@')){
            if (list[ip-2][jp]=='*'){
                list[ip-2][jp]='#';
                list[ip-1][jp]=' ';
                f++;
            }
            else{
                list[ip-2][jp]='@';
                list[ip-1][jp]=' ';
            }
            step++;
        }
        else if((ch=='s') && (list[ip+1][jp]=='@') && (list[ip+2][jp]!='#') && (list[ip+2][jp]!='@')){
            if (list[ip+2][jp]=='*'){
                list[ip+2][jp]='#';
                list[ip+1][jp]=' ';
                f++;
            }
            else{
                list[ip+2][jp]='@';
                list[ip+1][jp]=' ';
            }
            step++;
        }
        else if((ch=='a') && (list[ip][jp-1]=='@') && (list[ip][jp-2]!='#') && (list[ip][jp-2]!='@')){
            if (list[ip][jp-2]=='*'){
                list[ip][jp-2]='#';
                list[ip][jp-1]=' ';
                f++;
            }
            else{
                list[ip][jp-2]='@';
                list[ip][jp-1]=' ';
            }
            step++;
        }
        else if((ch=='d') && (list[ip][jp+1]=='@') && (list[ip][jp+2]!='#') && (list[ip][jp+2]!='@')){
            if (list[ip][jp+2]=='*'){
                list[ip][jp+2]='#';
                list[ip][jp+1]=' ';
                f++;
            }
            else{
                list[ip][jp+2]='@';
                list[ip][jp+1]=' ';
            }
            step++;
        }
    }
    system("cls");
    printf("you win!\n");
    printf("step:%d\n",step);
    system("pause");
    return 0;
}