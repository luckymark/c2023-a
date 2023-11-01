#include "push_boxes.h"
#include "windows.h"
#include "conio.h"
#include "math.h"

int main(){
    unsigned score = 0;
    char username[100]={}, **map, filename[]="001.bin";
    printf("please press in your username:");
    scanf("%s", username);
    printf("Welcome %s\n", username);
    Sleep(500);
    system("cls");
    printf("\x1b[?25l");
    for(unsigned i=1;i<3;i++){
        begin:
        score=0;
        system("cls");
        for(unsigned j=0;j< 3;j++){filename[j]=i/(unsigned )pow(10,2-j)%10+'0';}
        map = init_map(filename);
        draw_map(map);
        printf("\n\nfile: %s\nuser: %s\nscore: %d\n",filename, username, score);
        int ch;
        Place delta={0,0};
        while ((ch = getch()) != 0x1B) /* ESC to quit, up-72 down-80 left-75 right-77 */
        {
            if (ch == 224) {
                ch = getch();
                char tmp = 0;
                if (ch == 72) { delta.x = -1; delta.y = 0; }
                else if (ch == 80){ delta.x = 1; delta.y = 0; }
                else if (ch == 75){ delta.x = 0; delta.y = -1; }
                else if (ch == 77){ delta.x = 0; delta.y = 1; }

                if ((tmp = move(map, delta, &score))== 2) {
                    system("cls");
                    printf("You win!\n");
                    Sleep(500);
                    break;
                }
                system("cls");
                draw_map(map);
                printf("\n\nfile: %s\nuser: %s\nscore: %d\n",filename, username, score);

            }else if(ch==8) goto begin;
            else if(ch==13)break;
        }
    }
}