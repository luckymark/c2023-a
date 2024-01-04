#include "push_boxes.h"
#include "windows.h"
#include "conio.h"
#include "math.h"
#include "string.h"

int main(){
    unsigned score = 0;
    char username[100]={}, **map=NULL, filename[]="001.bin", prefix[]="D:\\YCM\\C++\\uestc\\c2023-a\\level1\\p08_push_boxes\\";
    unsigned prefix_len = strlen(prefix);
    printf("please press in your username:");
    scanf("%s", username);
    printf("Welcome %s\n", username);
    Sleep(500);
    system("cls");
    printf("\x1b[?25l");
    for(unsigned i=1;;i++){
        begin:
        score=0;
        system("cls");
        for(unsigned j=0;j< 3;j++){filename[j]=i/(unsigned )pow(10,2-j)%10+'0';}
        destroy_map(map);
        map = init_map(strcat(prefix,filename));

        prefix[prefix_len] = 0;
        if(map==NULL){
            system("cls");
            printf("You have passed all stages!\n");
            system("pause");
            break;
        }

        draw_map(map);
        printf("\n\nlegend:\t%c player\t%c box\n\t%c goal\t\t%c box in goal\nfile: %s\nuser: %s\nscore: %d\n",PLAYER_C, BOX_C, GOAL_C, FILL_C,filename, username, score);
        int ch;
        Place delta={0,0};
        while ((ch = getch()) != 0x1B) /* ESC to quit, up-72(w-87) down-80(s-83) left-75(a-65) right-77(d-68) */
        {
            if (ch==0||ch == 224||ch=='w'||ch=='s'||ch=='d'||ch=='a') {
                if(ch==224)ch = getch();
                if (ch == 72||ch=='w') { delta.x = -1; delta.y = 0; }
                if (ch == 80||ch=='s'){ delta.x = 1; delta.y = 0; }
                if (ch == 75||ch=='a'){ delta.x = 0; delta.y = -1; }
                if (ch == 77||ch=='d'){ delta.x = 0; delta.y = 1; }

                if (move(map, delta, &score)== 2) {
                    system("cls");
                    printf("You win!\n");
                    Sleep(500);
                    break;
                }
                system("cls");
                draw_map(map);
                printf("\n\nlegend:\t%c player\t%c box\n\t%c goal\t\t%c box in goal\nfile: %s\nuser: %s\nscore: %d\n",PLAYER_C, BOX_C, GOAL_C, FILL_C,filename, username, score);
            }else if(ch==8) goto begin;
            else if(ch==13)break;
        }
    }
}