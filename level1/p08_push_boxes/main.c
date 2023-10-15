#include "push_boxes.h"
int main()
{
    int n = 1;
    do{
        while(1){
            Game(n);
            int input;
            Color(7);
            gotoxy(40, 8);
            if(n<5)
            {
                printf("please choose:");
                gotoxy(40, 9);
                printf("1.go to the next level");
                gotoxy(40, 10);
                printf("2.restart");
                gotoxy(40, 11);
                scanf("%d", &input);
            }
            else
            {
                gotoxy(40,11);
                printf("Congratulation!");
                gotoxy(40,12);
                printf("You have passed all the level");
                break;
            }
            if (input == 1)
            {
                n++;
                system("cls");
            }
            if (input == 2)
            {
                system("cls");
                break;
            }
        }
    }while(n<5);
    system("pause");
    return 0;
}
