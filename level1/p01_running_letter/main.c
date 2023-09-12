#include <stdio.h>
#include <windows.h>
int main()
{   while(1)
    {
        for (int i = 0; i < 82; i++) {
            for (int j = 0; j < i; j++) {
                printf(" ");
            }
            printf("word");
            Sleep(50);
            system("cls");
        }
        for (int i = 82; i > 0; i--) {
            for (int j = 0; j < i; j++) {
                printf(" ");
            }
            printf("word");
            Sleep(50);
            system("cls");
        }
    }
    return 0;
}
